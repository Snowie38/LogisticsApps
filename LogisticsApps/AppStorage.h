#pragma once

// Общий слой хранения данных для приложения: DataSet + XML.
// Файл: logistics_storage.xml (рядом с exe).
// Используется в AdminWindow / ClientWindow / LoginWindow.

namespace LogisticsApp {

	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::Data;
	using namespace System::IO;
	using namespace System::Windows::Forms;

	public ref class OrderDraft sealed
	{
	public:
		// маршрут / груз
		String^ CityFrom;
		String^ CityTo;
		int DistanceKm;

		String^ CargoType;
		int CargoTypeIndex;

		double WeightKg;
		double VolumeM3;
		double LengthM;
		double DeclaredValue;

		// адреса и опции (из ClientWindow)
		bool PickupFromAddress;
		bool DeliveryToAddress;
		String^ FromAddress;
		String^ ToAddress;

		bool OptProtectPack;
		bool OptPallet;
		bool OptFloorDelivery;
		bool OptDocsA;
		bool OptDocsB;

		String^ DeliveryType; // "Экспресс"/"Стандарт"

		// расчёты
		double BaseCost;
		double OptionsCost;
		double InsuranceCost;
		double TotalCost;
	};

	public ref class AppStorage sealed
	{
	private:
		static DataSet^ _ds = nullptr;
		static DataTable^ _orders = nullptr;
		static DataTable^ _clients = nullptr;
		static DataTable^ _settings = nullptr;
		static String^ _path = nullptr;

		// --- helpers ---
		static void EnsureColumn(DataTable^ t, String^ name, Type^ type, Object^ defaultValue)
		{
			if (t == nullptr) return;
			if (!t->Columns->Contains(name))
			{
				DataColumn^ c = gcnew DataColumn(name, type);
				if (defaultValue != nullptr) c->DefaultValue = defaultValue;
				t->Columns->Add(c);
			}
		}
		// перегрузки, чтобы избежать C4965 (неявная упаковка 0/false)
		static void EnsureColumn(DataTable^ t, String^ name, Type^ type, int defaultValue)
		{
			EnsureColumn(t, name, type, safe_cast<Object^>(defaultValue));
		}
		static void EnsureColumn(DataTable^ t, String^ name, Type^ type, double defaultValue)
		{
			EnsureColumn(t, name, type, safe_cast<Object^>(defaultValue));
		}
		static void EnsureColumn(DataTable^ t, String^ name, Type^ type, bool defaultValue)
		{
			EnsureColumn(t, name, type, safe_cast<Object^>(defaultValue));
		}
		static void EnsureColumn(DataTable^ t, String^ name, Type^ type, DateTime defaultValue)
		{
			EnsureColumn(t, name, type, safe_cast<Object^>(defaultValue));
		}

		static bool IsNullOrEmptyValue(Object^ v)
		{
			if (v == nullptr || v == DBNull::Value) return true;

			String^ s = dynamic_cast<String^>(v);
			if (s != nullptr) return String::IsNullOrWhiteSpace(s);

			if (v->GetType() == DateTime::typeid)
			{
				DateTime dt = safe_cast<DateTime>(v);
				return dt == DateTime::MinValue;
			}

			return false;
		}

		// миграция имён колонок (если в старом XML были другие названия)
		static void MigrateColumnName(DataTable^ t, String^ oldName, String^ newName)
		{
			if (t == nullptr) return;
			if (!t->Columns->Contains(oldName)) return;

			if (!t->Columns->Contains(newName))
			{
				t->Columns[oldName]->ColumnName = newName;
				return;
			}

			for each (DataRow ^ r in t->Rows)
			{
				Object^ oldv = r[oldName];
				Object^ newv = r[newName];

				bool newEmpty = IsNullOrEmptyValue(newv);
				bool oldHas = !IsNullOrEmptyValue(oldv);

				if (newEmpty && oldHas)
					r[newName] = oldv;
			}

			t->Columns->Remove(oldName);
		}

		// --- schema builders ---
		static DataTable^ BuildOrders()
		{
			DataTable^ t = gcnew DataTable("Orders");

			DataColumn^ id = gcnew DataColumn("Id", Int32::typeid);
			id->AutoIncrement = true;
			id->AutoIncrementSeed = 1;
			id->AutoIncrementStep = 1;
			t->Columns->Add(id);
			t->PrimaryKey = gcnew array<DataColumn^>{ id };

			// отправитель / получатель (из LoginWindow)
			t->Columns->Add("SenderName", String::typeid);
			t->Columns->Add("SenderPhone", String::typeid);
			t->Columns->Add("SenderEmail", String::typeid);
			t->Columns->Add("SenderType", String::typeid);

			t->Columns->Add("RecipientName", String::typeid);
			t->Columns->Add("RecipientPhone", String::typeid);
			t->Columns->Add("RecipientEmail", String::typeid);
			t->Columns->Add("RecipientType", String::typeid);

			// доп. реквизиты (ИНН/организация/паспорт)
			t->Columns->Add("SenderInn", String::typeid);
			t->Columns->Add("SenderOrgName", String::typeid);
			t->Columns->Add("SenderOpf", String::typeid);
			t->Columns->Add("SenderKpp", String::typeid);
			t->Columns->Add("SenderPassSeries", String::typeid);
			t->Columns->Add("SenderPassNumber", String::typeid);
			t->Columns->Add("SenderPassDate", DateTime::typeid);

			t->Columns->Add("RecipientInn", String::typeid);
			t->Columns->Add("RecipientOrgName", String::typeid);
			t->Columns->Add("RecipientOpf", String::typeid);
			t->Columns->Add("RecipientKpp", String::typeid);
			t->Columns->Add("RecipientPassSeries", String::typeid);
			t->Columns->Add("RecipientPassNumber", String::typeid);
			t->Columns->Add("RecipientPassDate", DateTime::typeid);

			// маршрут / груз (из ClientWindow)
			t->Columns->Add("CityFrom", String::typeid);
			t->Columns->Add("CityTo", String::typeid);
			t->Columns->Add("DistanceKm", Int32::typeid);

			t->Columns->Add("CargoType", String::typeid);
			t->Columns->Add("CargoTypeIndex", Int32::typeid);
			t->Columns->Add("WeightKg", Double::typeid);
			t->Columns->Add("VolumeM3", Double::typeid);
			t->Columns->Add("LengthM", Double::typeid);
			t->Columns->Add("DeclaredValue", Double::typeid);

			// адреса / опции
			t->Columns->Add("PickupFromAddress", Boolean::typeid);
			t->Columns->Add("DeliveryToAddress", Boolean::typeid);
			t->Columns->Add("FromAddress", String::typeid);
			t->Columns->Add("ToAddress", String::typeid);

			t->Columns->Add("OptProtectPack", Boolean::typeid);
			t->Columns->Add("OptPallet", Boolean::typeid);
			t->Columns->Add("OptFloorDelivery", Boolean::typeid);
			t->Columns->Add("OptDocsA", Boolean::typeid);
			t->Columns->Add("OptDocsB", Boolean::typeid);

			t->Columns->Add("DeliveryType", String::typeid);

			// стоимость
			t->Columns->Add("BaseCost", Double::typeid);
			t->Columns->Add("OptionsCost", Double::typeid);
			t->Columns->Add("InsuranceCost", Double::typeid);
			t->Columns->Add("TotalCost", Double::typeid);

			// статус / время
			t->Columns->Add("Status", String::typeid);
			t->Columns->Add("CreatedAt", DateTime::typeid);
			t->Columns->Add("UpdatedAt", DateTime::typeid);

			t->Columns["Status"]->DefaultValue = "Создан";
			t->Columns["CreatedAt"]->DefaultValue = DateTime::Now;
			t->Columns["UpdatedAt"]->DefaultValue = DateTime::Now;

			t->Columns["SenderEmail"]->DefaultValue = "";
			t->Columns["RecipientEmail"]->DefaultValue = "";

			return t;
		}

		static DataTable^ BuildClients()
		{
			DataTable^ t = gcnew DataTable("Clients");

			DataColumn^ id = gcnew DataColumn("Id", Int32::typeid);
			id->AutoIncrement = true;
			id->AutoIncrementSeed = 1;
			id->AutoIncrementStep = 1;
			t->Columns->Add(id);
			t->PrimaryKey = gcnew array<DataColumn^>{ id };

			t->Columns->Add("Name", String::typeid);
			t->Columns->Add("Phone", String::typeid);
			t->Columns->Add("Email", String::typeid);

			t->Columns->Add("ClientType", String::typeid); // Физ. лицо / ИП / Юр. лицо
			t->Columns->Add("Inn", String::typeid);
			t->Columns->Add("OrgName", String::typeid);
			t->Columns->Add("Opf", String::typeid);
			t->Columns->Add("Kpp", String::typeid);

			t->Columns->Add("PassSeries", String::typeid);
			t->Columns->Add("PassNumber", String::typeid);
			t->Columns->Add("PassDate", DateTime::typeid);

			return t;
		}

		static DataTable^ BuildSettings()
		{
			DataTable^ t = gcnew DataTable("Settings");
			DataColumn^ key = gcnew DataColumn("Key", String::typeid);
			t->Columns->Add(key);
			t->PrimaryKey = gcnew array<DataColumn^>{ key };

			// числовые настройки
			t->Columns->Add("Value", Double::typeid);

			// строковые настройки (например пароль администратора)
			t->Columns->Add("ValueStr", String::typeid);

			t->Columns->Add("Note", String::typeid);
			return t;
		}

		// --- seeding ---
		static void SeedSetting(String^ key, double value, String^ note)
		{
			DataRow^ r = _settings->Rows->Find(key);
			if (r != nullptr) return;

			r = _settings->NewRow();
			r["Key"] = key;
			r["Value"] = value;
			r["ValueStr"] = "";
			r["Note"] = note;
			_settings->Rows->Add(r);
		}

		static void SeedSettingStr(String^ key, String^ value, String^ note)
		{
			DataRow^ r = _settings->Rows->Find(key);
			if (r != nullptr) return;

			r = _settings->NewRow();
			r["Key"] = key;
			r["Value"] = 0.0;
			r["ValueStr"] = value;
			r["Note"] = note;
			_settings->Rows->Add(r);
		}

		static void SeedDefaults()
		{
			// Базовые тарифы
			SeedSetting("RatePerKm", 12.0, "Стоимость за 1 км");
			SeedSetting("RatePerKg", 15.0, "Стоимость за 1 кг");
			SeedSetting("RatePerM3", 120.0, "Стоимость за 1 м^3");
			SeedSetting("RatePerM", 50.0, "Стоимость за 1 метр длины");

			// Множители / проценты
			SeedSetting("ExpressMultiplier", 1.25, "Экспресс: множитель");
			SeedSetting("InsurancePercent", 0.5, "Страховка: % от объявленной стоимости");

			// Адресные услуги
			SeedSetting("PickupFee", 710.0, "Забор от адреса");
			SeedSetting("DeliveryFee", 510.0, "Доставка до адреса");

			// Доп. опции
			SeedSetting("ProtectPackFee", 510.0, "Защитная упаковка");
			SeedSetting("PalletFee", 600.0, "Палетирование");
			SeedSetting("FloorDeliveryFee", 0.0, "Доставка на этаж");
			SeedSetting("DocsFeeA", 150.0, "Документы A");
			SeedSetting("DocsFeeB", 100.0, "Документы B");

			// Коэффициенты типа груза
			SeedSetting("CargoCoef_0", 1.00, "Обычный");
			SeedSetting("CargoCoef_1", 1.20, "Хрупкое");
			SeedSetting("CargoCoef_2", 0.90, "Документы");
			SeedSetting("CargoCoef_3", 1.50, "Крупногабаритный");
			SeedSetting("CargoCoef_4", 1.70, "Топливо");
			SeedSetting("CargoCoef_5", 2.00, "Газ");
			SeedSetting("CargoCoef_6", 3.00, "Радиоактивные");

			// Пароль администратора
			SeedSettingStr("AdminPassword", "1111", "Пароль администратора");
		}

		// --- schema upgrade ---
		static void EnsureSchemasAfterLoad()
		{
			// миграция старых названий паспортных полей (*Passport* -> *Pass*)
			MigrateColumnName(_orders, "SenderPassportSeries", "SenderPassSeries");
			MigrateColumnName(_orders, "SenderPassportNumber", "SenderPassNumber");
			MigrateColumnName(_orders, "SenderPassportDate", "SenderPassDate");
			MigrateColumnName(_orders, "RecipientPassportSeries", "RecipientPassSeries");
			MigrateColumnName(_orders, "RecipientPassportNumber", "RecipientPassNumber");
			MigrateColumnName(_orders, "RecipientPassportDate", "RecipientPassDate");

			// Orders
			EnsureColumn(_orders, "SenderName", String::typeid, "");
			EnsureColumn(_orders, "SenderPhone", String::typeid, "");
			EnsureColumn(_orders, "SenderEmail", String::typeid, "");
			EnsureColumn(_orders, "SenderType", String::typeid, "");

			EnsureColumn(_orders, "RecipientName", String::typeid, "");
			EnsureColumn(_orders, "RecipientPhone", String::typeid, "");
			EnsureColumn(_orders, "RecipientEmail", String::typeid, "");
			EnsureColumn(_orders, "RecipientType", String::typeid, "");

			EnsureColumn(_orders, "SenderInn", String::typeid, "");
			EnsureColumn(_orders, "SenderOrgName", String::typeid, "");
			EnsureColumn(_orders, "SenderOpf", String::typeid, "");
			EnsureColumn(_orders, "SenderKpp", String::typeid, "");
			EnsureColumn(_orders, "SenderPassSeries", String::typeid, "");
			EnsureColumn(_orders, "SenderPassNumber", String::typeid, "");
			EnsureColumn(_orders, "SenderPassDate", DateTime::typeid, DateTime::MinValue);

			EnsureColumn(_orders, "RecipientInn", String::typeid, "");
			EnsureColumn(_orders, "RecipientOrgName", String::typeid, "");
			EnsureColumn(_orders, "RecipientOpf", String::typeid, "");
			EnsureColumn(_orders, "RecipientKpp", String::typeid, "");
			EnsureColumn(_orders, "RecipientPassSeries", String::typeid, "");
			EnsureColumn(_orders, "RecipientPassNumber", String::typeid, "");
			EnsureColumn(_orders, "RecipientPassDate", DateTime::typeid, DateTime::MinValue);

			EnsureColumn(_orders, "CityFrom", String::typeid, "");
			EnsureColumn(_orders, "CityTo", String::typeid, "");
			EnsureColumn(_orders, "DistanceKm", Int32::typeid, 0);

			EnsureColumn(_orders, "CargoType", String::typeid, "");
			EnsureColumn(_orders, "CargoTypeIndex", Int32::typeid, 0);
			EnsureColumn(_orders, "WeightKg", Double::typeid, 0.0);
			EnsureColumn(_orders, "VolumeM3", Double::typeid, 0.0);
			EnsureColumn(_orders, "LengthM", Double::typeid, 0.0);
			EnsureColumn(_orders, "DeclaredValue", Double::typeid, 0.0);

			EnsureColumn(_orders, "PickupFromAddress", Boolean::typeid, false);
			EnsureColumn(_orders, "DeliveryToAddress", Boolean::typeid, false);
			EnsureColumn(_orders, "FromAddress", String::typeid, "");
			EnsureColumn(_orders, "ToAddress", String::typeid, "");

			EnsureColumn(_orders, "OptProtectPack", Boolean::typeid, false);
			EnsureColumn(_orders, "OptPallet", Boolean::typeid, false);
			EnsureColumn(_orders, "OptFloorDelivery", Boolean::typeid, false);
			EnsureColumn(_orders, "OptDocsA", Boolean::typeid, false);
			EnsureColumn(_orders, "OptDocsB", Boolean::typeid, false);

			EnsureColumn(_orders, "DeliveryType", String::typeid, "");

			EnsureColumn(_orders, "BaseCost", Double::typeid, 0.0);
			EnsureColumn(_orders, "OptionsCost", Double::typeid, 0.0);
			EnsureColumn(_orders, "InsuranceCost", Double::typeid, 0.0);
			EnsureColumn(_orders, "TotalCost", Double::typeid, 0.0);

			EnsureColumn(_orders, "Status", String::typeid, "Создан");
			EnsureColumn(_orders, "CreatedAt", DateTime::typeid, DateTime::Now);
			EnsureColumn(_orders, "UpdatedAt", DateTime::typeid, DateTime::Now);

			// Clients
			EnsureColumn(_clients, "Name", String::typeid, "");
			EnsureColumn(_clients, "Phone", String::typeid, "");
			EnsureColumn(_clients, "Email", String::typeid, "");

			EnsureColumn(_clients, "ClientType", String::typeid, "");
			EnsureColumn(_clients, "Inn", String::typeid, "");
			EnsureColumn(_clients, "OrgName", String::typeid, "");
			EnsureColumn(_clients, "Opf", String::typeid, "");
			EnsureColumn(_clients, "Kpp", String::typeid, "");
			EnsureColumn(_clients, "PassSeries", String::typeid, "");
			EnsureColumn(_clients, "PassNumber", String::typeid, "");
			EnsureColumn(_clients, "PassDate", DateTime::typeid, DateTime::MinValue);

			// Settings
			EnsureColumn(_settings, "Value", Double::typeid, 0.0);
			EnsureColumn(_settings, "ValueStr", String::typeid, "");
			EnsureColumn(_settings, "Note", String::typeid, "");

			// defaults if missing
			SeedDefaults();
		}

		static void UpsertClient(
			String^ name, String^ phone, String^ email, String^ clientType,
			String^ inn, String^ orgName, String^ opf, String^ kpp,
			String^ passSeries, String^ passNumber, DateTime passDate)
		{
			if (String::IsNullOrWhiteSpace(phone)) return;

			// ищем по телефону
			for each (DataRow ^ c in _clients->Rows)
			{
				if (c->RowState == DataRowState::Deleted) continue;
				String^ p = c["Phone"] != nullptr ? Convert::ToString(c["Phone"]) : "";
				if (!String::Equals(p, phone)) continue;

				// обновляем только пустые поля (или если пришло "лучшее" значение)
				if (!String::IsNullOrWhiteSpace(name))
				{
					String^ n0 = c["Name"] != nullptr ? Convert::ToString(c["Name"]) : "";
					if (String::IsNullOrWhiteSpace(n0)) c["Name"] = name;
				}

				if (!String::IsNullOrWhiteSpace(email))
				{
					String^ e0 = c["Email"] != nullptr ? Convert::ToString(c["Email"]) : "";
					if (String::IsNullOrWhiteSpace(e0)) c["Email"] = email;
				}

				if (!String::IsNullOrWhiteSpace(clientType))
				{
					String^ t0 = c["ClientType"] != nullptr ? Convert::ToString(c["ClientType"]) : "";
					if (String::IsNullOrWhiteSpace(t0)) c["ClientType"] = clientType;
				}

				if (!String::IsNullOrWhiteSpace(inn))
				{
					String^ v0 = c["Inn"] != nullptr ? Convert::ToString(c["Inn"]) : "";
					if (String::IsNullOrWhiteSpace(v0)) c["Inn"] = inn;
				}
				if (!String::IsNullOrWhiteSpace(orgName))
				{
					String^ v0 = c["OrgName"] != nullptr ? Convert::ToString(c["OrgName"]) : "";
					if (String::IsNullOrWhiteSpace(v0)) c["OrgName"] = orgName;
				}
				if (!String::IsNullOrWhiteSpace(opf))
				{
					String^ v0 = c["Opf"] != nullptr ? Convert::ToString(c["Opf"]) : "";
					if (String::IsNullOrWhiteSpace(v0)) c["Opf"] = opf;
				}
				if (!String::IsNullOrWhiteSpace(kpp))
				{
					String^ v0 = c["Kpp"] != nullptr ? Convert::ToString(c["Kpp"]) : "";
					if (String::IsNullOrWhiteSpace(v0)) c["Kpp"] = kpp;
				}

				if (!String::IsNullOrWhiteSpace(passSeries))
				{
					String^ v0 = c["PassSeries"] != nullptr ? Convert::ToString(c["PassSeries"]) : "";
					if (String::IsNullOrWhiteSpace(v0)) c["PassSeries"] = passSeries;
				}
				if (!String::IsNullOrWhiteSpace(passNumber))
				{
					String^ v0 = c["PassNumber"] != nullptr ? Convert::ToString(c["PassNumber"]) : "";
					if (String::IsNullOrWhiteSpace(v0)) c["PassNumber"] = passNumber;
				}
				if (passDate != DateTime::MinValue)
				{
					DateTime d0 = DateTime::MinValue;
					try { d0 = safe_cast<DateTime>(c["PassDate"]); }
					catch (...) { d0 = DateTime::MinValue; }
					if (d0 == DateTime::MinValue) c["PassDate"] = passDate;
				}

				return;
			}

			// не нашли — создаём
			DataRow^ r = _clients->NewRow();
			r["Name"] = name;
			r["Phone"] = phone;
			r["Email"] = email;

			r["ClientType"] = clientType;
			r["Inn"] = inn;
			r["OrgName"] = orgName;
			r["Opf"] = opf;
			r["Kpp"] = kpp;

			r["PassSeries"] = passSeries;
			r["PassNumber"] = passNumber;
			r["PassDate"] = passDate;

			_clients->Rows->Add(r);
		}

	public:
		static void Init()
		{
			if (_ds != nullptr) return;

			_path = Path::Combine(Application::StartupPath, "logistics_storage.xml");
			_ds = gcnew DataSet("LogisticsStorage");

			if (File::Exists(_path))
			{
				_ds->ReadXml(_path, XmlReadMode::ReadSchema);
				if (_ds->Tables->Contains("Orders")) _orders = _ds->Tables["Orders"];
				if (_ds->Tables->Contains("Clients")) _clients = _ds->Tables["Clients"];
				if (_ds->Tables->Contains("Settings")) _settings = _ds->Tables["Settings"];
			}

			if (_orders == nullptr) { _orders = BuildOrders(); _ds->Tables->Add(_orders); }
			if (_clients == nullptr) { _clients = BuildClients(); _ds->Tables->Add(_clients); }
			if (_settings == nullptr) { _settings = BuildSettings(); _ds->Tables->Add(_settings); }

			EnsureSchemasAfterLoad();
			Save();
		}

		static void Save()
		{
			Init();
			_ds->WriteXml(_path, XmlWriteMode::WriteSchema);
		}

		static DataTable^ Orders() { Init(); return _orders; }
		static DataTable^ Clients() { Init(); return _clients; }
		static DataTable^ Settings() { Init(); return _settings; }

		static double GetSetting(String^ key, double fallback)
		{
			Init();
			DataRow^ r = _settings->Rows->Find(key);
			if (r == nullptr) return fallback;
			try { return Convert::ToDouble(r["Value"]); }
			catch (...) { return fallback; }
		}

		static void UpdateSetting(String^ key, double value)
		{
			Init();
			DataRow^ r = _settings->Rows->Find(key);
			if (r == nullptr)
			{
				r = _settings->NewRow();
				r["Key"] = key;
				r["Value"] = value;
				r["ValueStr"] = "";
				r["Note"] = "";
				_settings->Rows->Add(r);
			}
			else
			{
				r["Value"] = value;
			}
			Save();
		}

		static String^ GetSettingStr(String^ key, String^ fallback)
		{
			Init();
			DataRow^ r = _settings->Rows->Find(key);
			if (r == nullptr) return fallback;

			try
			{
				if (_settings->Columns->Contains("ValueStr"))
				{
					String^ s = r["ValueStr"] != nullptr ? Convert::ToString(r["ValueStr"]) : "";
					if (!String::IsNullOrWhiteSpace(s)) return s;
				}
			}
			catch (...) {}

			return fallback;
		}

		static void UpdateSettingStr(String^ key, String^ value)
		{
			Init();
			DataRow^ r = _settings->Rows->Find(key);
			if (r == nullptr)
			{
				r = _settings->NewRow();
				r["Key"] = key;
				r["Value"] = 0.0;
				r["ValueStr"] = value;
				r["Note"] = "";
				_settings->Rows->Add(r);
			}
			else
			{
				if (_settings->Columns->Contains("ValueStr"))
					r["ValueStr"] = value;
			}
			Save();
		}

		static String^ GetAdminPassword()
		{
			return GetSettingStr("AdminPassword", "1111");
		}

		static void SetAdminPassword(String^ newPass)
		{
			if (newPass == nullptr) newPass = "";
			UpdateSettingStr("AdminPassword", newPass);
		}

		// Расширенная перегрузка AddOrder — соответствует данным из LoginWindow (оформление заказа)
		static int AddOrder(
			OrderDraft^ d,
			String^ senderName, String^ senderPhone, String^ senderEmail, String^ senderType,
			String^ recipientName, String^ recipientPhone, String^ recipientEmail, String^ recipientType,
			String^ senderInn, String^ senderOrgName, String^ senderOpf, String^ senderKpp,
			String^ senderPassSeries, String^ senderPassNumber, DateTime senderPassDate,
			String^ recipientInn, String^ recipientOrgName, String^ recipientOpf, String^ recipientKpp,
			String^ recipientPassSeries, String^ recipientPassNumber, DateTime recipientPassDate)
		{
			Init();
			if (d == nullptr) return -1;

			DataRow^ r = _orders->NewRow();
			r["SenderName"] = senderName;
			r["SenderPhone"] = senderPhone;
			r["SenderEmail"] = senderEmail;
			r["SenderType"] = senderType;

			r["RecipientName"] = recipientName;
			r["RecipientPhone"] = recipientPhone;
			r["RecipientEmail"] = recipientEmail;
			r["RecipientType"] = recipientType;

			r["SenderInn"] = senderInn;
			r["SenderOrgName"] = senderOrgName;
			r["SenderOpf"] = senderOpf;
			r["SenderKpp"] = senderKpp;
			r["SenderPassSeries"] = senderPassSeries;
			r["SenderPassNumber"] = senderPassNumber;
			r["SenderPassDate"] = senderPassDate;

			r["RecipientInn"] = recipientInn;
			r["RecipientOrgName"] = recipientOrgName;
			r["RecipientOpf"] = recipientOpf;
			r["RecipientKpp"] = recipientKpp;
			r["RecipientPassSeries"] = recipientPassSeries;
			r["RecipientPassNumber"] = recipientPassNumber;
			r["RecipientPassDate"] = recipientPassDate;

			r["CityFrom"] = d->CityFrom;
			r["CityTo"] = d->CityTo;
			r["DistanceKm"] = d->DistanceKm;

			r["CargoType"] = d->CargoType;
			r["CargoTypeIndex"] = d->CargoTypeIndex;
			r["WeightKg"] = d->WeightKg;
			r["VolumeM3"] = d->VolumeM3;
			r["LengthM"] = d->LengthM;
			r["DeclaredValue"] = d->DeclaredValue;

			r["PickupFromAddress"] = d->PickupFromAddress;
			r["DeliveryToAddress"] = d->DeliveryToAddress;
			r["FromAddress"] = d->FromAddress;
			r["ToAddress"] = d->ToAddress;

			r["OptProtectPack"] = d->OptProtectPack;
			r["OptPallet"] = d->OptPallet;
			r["OptFloorDelivery"] = d->OptFloorDelivery;
			r["OptDocsA"] = d->OptDocsA;
			r["OptDocsB"] = d->OptDocsB;

			r["DeliveryType"] = d->DeliveryType;

			r["BaseCost"] = d->BaseCost;
			r["OptionsCost"] = d->OptionsCost;
			r["InsuranceCost"] = d->InsuranceCost;
			r["TotalCost"] = d->TotalCost;

			r["Status"] = "Создан";
			r["CreatedAt"] = DateTime::Now;
			r["UpdatedAt"] = DateTime::Now;

			_orders->Rows->Add(r);

			// Добавим/обновим клиентов (и отправителя, и получателя)
			UpsertClient(senderName, senderPhone, senderEmail, senderType,
				senderInn, senderOrgName, senderOpf, senderKpp,
				senderPassSeries, senderPassNumber, senderPassDate);

			UpsertClient(recipientName, recipientPhone, recipientEmail, recipientType,
				recipientInn, recipientOrgName, recipientOpf, recipientKpp,
				recipientPassSeries, recipientPassNumber, recipientPassDate);

			Save();
			return Convert::ToInt32(r["Id"]);
		}

		// Алиасы для совместимости со старыми вызовами (если где-то остались)
		static int AddOrderEx(
			OrderDraft^ d,
			String^ senderName, String^ senderPhone, String^ senderEmail, String^ senderType,
			String^ recipientName, String^ recipientPhone, String^ recipientEmail, String^ recipientType,
			String^ senderInn, String^ senderOrgName, String^ senderOpf, String^ senderKpp,
			String^ senderPassSeries, String^ senderPassNumber, DateTime senderPassDate,
			String^ recipientInn, String^ recipientOrgName, String^ recipientOpf, String^ recipientKpp,
			String^ recipientPassSeries, String^ recipientPassNumber, DateTime recipientPassDate)
		{
			return AddOrder(d,
				senderName, senderPhone, senderEmail, senderType,
				recipientName, recipientPhone, recipientEmail, recipientType,
				senderInn, senderOrgName, senderOpf, senderKpp,
				senderPassSeries, senderPassNumber, senderPassDate,
				recipientInn, recipientOrgName, recipientOpf, recipientKpp,
				recipientPassSeries, recipientPassNumber, recipientPassDate);
		}

		static int AddOrder(
			OrderDraft^ d,
			String^ senderName, String^ senderPhone, String^ senderType,
			String^ recipientName, String^ recipientPhone, String^ recipientType,
			String^ senderInn, String^ senderOrgName, String^ senderOpf, String^ senderKpp,
			String^ senderPassSeries, String^ senderPassNumber, DateTime senderPassDate,
			String^ recipientInn, String^ recipientOrgName, String^ recipientOpf, String^ recipientKpp,
			String^ recipientPassSeries, String^ recipientPassNumber, DateTime recipientPassDate)
		{
			return AddOrder(d,
				senderName, senderPhone, "", senderType,
				recipientName, recipientPhone, "", recipientType,
				senderInn, senderOrgName, senderOpf, senderKpp,
				senderPassSeries, senderPassNumber, senderPassDate,
				recipientInn, recipientOrgName, recipientOpf, recipientKpp,
				recipientPassSeries, recipientPassNumber, recipientPassDate);
		}

		static int AddOrder(
			OrderDraft^ d,
			String^ senderName, String^ senderPhone, String^ senderType,
			String^ recipientName, String^ recipientPhone, String^ recipientType)
		{
			return AddOrder(d,
				senderName, senderPhone, "", senderType,
				recipientName, recipientPhone, "", recipientType,
				"", "", "", "",
				"", "", DateTime::MinValue,
				"", "", "", "",
				"", "", DateTime::MinValue);
		}

		static int AddOrderEx(
			OrderDraft^ d,
			String^ senderName, String^ senderPhone, String^ senderType,
			String^ recipientName, String^ recipientPhone, String^ recipientType)
		{
			return AddOrder(d, senderName, senderPhone, senderType, recipientName, recipientPhone, recipientType);
		}
	};

}
