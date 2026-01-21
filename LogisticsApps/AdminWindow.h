#pragma once

// AdminWindow полностью на коде (без дизайнера).
// Хранилище данных: DataSet + XML (logistics_storage.xml рядом с exe).
// Страницы:
//  - Главная: дашборд (кол-во заказов, выручка, активные)
//  - Заказы: таблица заказов + смена статуса
//  - Клиенты: база клиентов + история заказов выбранного клиента
//  - Настройки стоимости: коэффициенты/цены доп.опций (сохраняются в Settings)

namespace LogisticsApp {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace System::Windows::Forms;

    // ====================== Storage: DataSet + XML ======================
    public ref class AppStorage sealed
    {
    private:
        static DataSet^ _ds = nullptr;
        static DataTable^ _orders = nullptr;
        static DataTable^ _clients = nullptr;
        static DataTable^ _settings = nullptr;
        static String^ _path = nullptr;

        static DataTable^ BuildOrders()
        {
            DataTable^ t = gcnew DataTable("Orders");

            DataColumn^ id = gcnew DataColumn("Id", Int32::typeid);
            id->AutoIncrement = true;
            id->AutoIncrementSeed = 1;
            id->AutoIncrementStep = 1;
            t->Columns->Add(id);
            t->PrimaryKey = gcnew array<DataColumn^>{ id };

            // Кому / от кого (минимально, можно расширять)
            t->Columns->Add("ClientName", String::typeid);     // клиент/получатель
            t->Columns->Add("ClientPhone", String::typeid);
            t->Columns->Add("SenderName", String::typeid);
            t->Columns->Add("SenderPhone", String::typeid);

            // Маршрут
            t->Columns->Add("CityFrom", String::typeid);
            t->Columns->Add("CityTo", String::typeid);
            t->Columns->Add("DistanceKm", Double::typeid);

            // Груз
            t->Columns->Add("CargoType", String::typeid);
            t->Columns->Add("WeightKg", Double::typeid);
            t->Columns->Add("VolumeM3", Double::typeid);
            t->Columns->Add("LengthM", Double::typeid);
            t->Columns->Add("DeclaredValue", Double::typeid);

            // Итоги
            t->Columns->Add("BaseCost", Double::typeid);
            t->Columns->Add("ServicesCost", Double::typeid);
            t->Columns->Add("TotalCost", Double::typeid);

            // Статус/время
            t->Columns->Add("Status", String::typeid);
            t->Columns->Add("CreatedAt", DateTime::typeid);
            t->Columns->Add("UpdatedAt", DateTime::typeid);

            t->Columns["Status"]->DefaultValue = "Создан";
            t->Columns["CreatedAt"]->DefaultValue = DateTime::Now;
            t->Columns["UpdatedAt"]->DefaultValue = DateTime::Now;

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

            // уникальность телефона на уровне логики, в DataTable уникальность можно так:
            t->Columns["Phone"]->Unique = false; // оставим false, чтобы не падать при кривых данных

            return t;
        }

        static DataTable^ BuildSettings()
        {
            DataTable^ t = gcnew DataTable("Settings");

            DataColumn^ key = gcnew DataColumn("Key", String::typeid);
            t->Columns->Add(key);
            t->PrimaryKey = gcnew array<DataColumn^>{ key };

            t->Columns->Add("Value", Double::typeid);
            t->Columns->Add("Note", String::typeid);

            return t;
        }

        static void SeedDefaultSettings()
        {
            // Значения по умолчанию (можно менять в UI)
            SetSetting("InsurancePercent", 2.0, "Страховка, % от объявленной стоимости");
            SetSetting("ExpressMultiplier", 1.25, "Множитель экспресс-доставки");
            SetSetting("FragileSurcharge", 500.0, "Надбавка за хрупкий груз, руб");
            SetSetting("PickupFee", 400.0, "Забор от адреса, руб");
            SetSetting("DeliveryFee", 400.0, "Доставка до адреса, руб");
            SetSetting("PackagingFee", 300.0, "Упаковка, руб");

            SetSetting("CargoCoef_Standard", 1.00, "Коэффициент груза: стандарт");
            SetSetting("CargoCoef_Documents", 0.85, "Коэффициент груза: документы");
            SetSetting("CargoCoef_Oversize", 1.15, "Коэффициент груза: крупногабарит");
        }

        static void SetSetting(String^ key, double value, String^ note)
        {
            DataRow^ r = _settings->Rows->Find(key);
            if (r == nullptr)
            {
                r = _settings->NewRow();
                r["Key"] = key;
                r["Value"] = value;
                r["Note"] = note;
                _settings->Rows->Add(r);
            }
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

            if (_orders == nullptr)
            {
                _orders = BuildOrders();
                _ds->Tables->Add(_orders);
            }
            if (_clients == nullptr)
            {
                _clients = BuildClients();
                _ds->Tables->Add(_clients);
            }
            if (_settings == nullptr)
            {
                _settings = BuildSettings();
                _ds->Tables->Add(_settings);
                SeedDefaultSettings();
            }

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
                r["Note"] = "";
                _settings->Rows->Add(r);
            }
            else
            {
                r["Value"] = value;
            }
            Save();
        }
    };

    // ============================ AdminWindow ============================
    public ref class AdminWindow : public Form
    {
    public:
        AdminWindow(void)
        {
            InitializeComponent();
            AppStorage::Init();
            BuildAdminUI();
            ShowPage("Главная");
            RefreshDashboard();
        }

    protected:
        ~AdminWindow()
        {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        // ===== UI общие =====
        Panel^ pnSidebar;
        Panel^ pnTop;
        Panel^ pnContent;
        Label^ lblTitle;

        Dictionary<String^, Panel^>^ pages;
        Dictionary<String^, Button^>^ navButtons;

        // ===== Главная (Dashboard) =====
        Label^ lblStatOrders;
        Label^ lblStatRevenue;
        Label^ lblStatActive;

        // ===== Заказы =====
        DataGridView^ dgvOrders;
        ComboBox^ cbStatus;
        Button^ btnApplyStatus;
        Button^ btnDeleteOrder;

        // ===== Клиенты =====
        DataGridView^ dgvClients;
        DataGridView^ dgvClientOrders;
        DataView^ clientOrdersView;
        Button^ btnSyncClients;

        // ===== Настройки стоимости =====
        Dictionary<String^, NumericUpDown^>^ settingEditors;
        Button^ btnSaveSettings;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->SuspendLayout();
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1500, 820);
            this->Name = L"AdminWindow";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Администрирование";
            this->ResumeLayout(false);
        }
#pragma endregion

        // =========================== Styling helpers ===========================
        Color C_Back() { return Color::FromArgb(240, 242, 245); }
        Color C_Side() { return Color::FromArgb(32, 36, 48); }
        Color C_SideHover() { return Color::FromArgb(55, 63, 85); }
        Color C_TextDark() { return Color::FromArgb(40, 40, 40); }

        Drawing::Font^ F_Title() { return gcnew Drawing::Font(L"Segoe UI", 14, FontStyle::Bold); }
        Drawing::Font^ F_Body() { return gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Regular); }
        Drawing::Font^ F_Bold() { return gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold); }

        void StyleNavButton(Button^ btn)
        {
            btn->Dock = DockStyle::Top;
            btn->Height = 48;
            btn->FlatStyle = FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 0;
            btn->TextAlign = ContentAlignment::MiddleLeft;
            btn->Padding = System::Windows::Forms::Padding(16, 0, 0, 0);
            btn->Font = F_Body();
            btn->ForeColor = Color::FromArgb(220, 220, 220);
            btn->BackColor = C_Side();
            btn->Cursor = Cursors::Hand;
        }

        void StylePrimaryButton(Button^ btn)
        {
            btn->FlatStyle = FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 0;
            btn->BackColor = C_SideHover();
            btn->ForeColor = Color::White;
            btn->Font = F_Bold();
            btn->Height = 38;
            btn->Cursor = Cursors::Hand;
        }

        Panel^ MakeCard(int x, int y, int w, int h)
        {
            Panel^ card = gcnew Panel();
            card->BackColor = Color::White;
            card->BorderStyle = BorderStyle::FixedSingle;
            card->Location = Point(x, y);
            card->Size = Drawing::Size(w, h);
            return card;
        }

        void StyleGrid(DataGridView^ g)
        {
            g->Dock = DockStyle::Fill;
            g->BackgroundColor = Color::White;
            g->BorderStyle = BorderStyle::None;
            g->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            g->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            g->MultiSelect = false;
            g->ReadOnly = true;
            g->AllowUserToAddRows = false;
            g->AllowUserToDeleteRows = false;
            g->RowHeadersVisible = false;

            g->EnableHeadersVisualStyles = false;
            g->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(245, 246, 248);
            g->ColumnHeadersDefaultCellStyle->ForeColor = C_TextDark();
            g->ColumnHeadersDefaultCellStyle->Font = F_Bold();
            g->DefaultCellStyle->Font = F_Body();
            g->DefaultCellStyle->ForeColor = C_TextDark();
            g->DefaultCellStyle->SelectionBackColor = Color::FromArgb(210, 220, 235);
            g->DefaultCellStyle->SelectionForeColor = C_TextDark();
        }

        // =========================== UI build ===========================
        void BuildAdminUI()
        {
            this->SuspendLayout();
            this->BackColor = C_Back();

            pages = gcnew Dictionary<String^, Panel^>();
            navButtons = gcnew Dictionary<String^, Button^>();
            settingEditors = gcnew Dictionary<String^, NumericUpDown^>();

            // ===== Sidebar =====
            pnSidebar = gcnew Panel();
            pnSidebar->Dock = DockStyle::Left;
            pnSidebar->Width = 260;
            pnSidebar->BackColor = C_Side();

            Panel^ pnSidebarTop = gcnew Panel();
            pnSidebarTop->Dock = DockStyle::Top;
            pnSidebarTop->Height = 90;
            pnSidebarTop->BackColor = C_Side();

            Panel^ pnSidebarBottom = gcnew Panel();
            pnSidebarBottom->Dock = DockStyle::Bottom;
            pnSidebarBottom->Height = 90;
            pnSidebarBottom->BackColor = C_Side();

            Panel^ pnSidebarMenu = gcnew Panel();
            pnSidebarMenu->Dock = DockStyle::Fill;
            pnSidebarMenu->BackColor = C_Side();

            pnSidebar->Controls->Add(pnSidebarBottom);
            pnSidebar->Controls->Add(pnSidebarMenu);
            pnSidebar->Controls->Add(pnSidebarTop);

            Label^ lblLogo = gcnew Label();
            lblLogo->Dock = DockStyle::Fill;
            lblLogo->Text = L"LOGISTICS\nADMIN";
            lblLogo->ForeColor = Color::White;
            lblLogo->TextAlign = ContentAlignment::MiddleCenter;
            lblLogo->Font = gcnew Drawing::Font(L"Segoe UI", 12, FontStyle::Bold);
            pnSidebarTop->Controls->Add(lblLogo);

            // ===== Main =====
            Panel^ pnMain = gcnew Panel();
            pnMain->Dock = DockStyle::Fill;
            pnMain->BackColor = C_Back();

            pnTop = gcnew Panel();
            pnTop->Dock = DockStyle::Top;
            pnTop->Height = 60;
            pnTop->BackColor = Color::White;

            lblTitle = gcnew Label();
            lblTitle->Dock = DockStyle::Fill;
            lblTitle->TextAlign = ContentAlignment::MiddleLeft;
            lblTitle->Font = F_Title();
            lblTitle->ForeColor = C_TextDark();
            lblTitle->Padding = System::Windows::Forms::Padding(16, 0, 0, 0);
            lblTitle->Text = L"Админ-панель";
            pnTop->Controls->Add(lblTitle);

            pnContent = gcnew Panel();
            pnContent->Dock = DockStyle::Fill;
            pnContent->BackColor = C_Back();

            pnMain->Controls->Add(pnContent);
            pnMain->Controls->Add(pnTop);

            this->Controls->Add(pnMain);
            this->Controls->Add(pnSidebar);

            // ===== Навигация (добавляем снизу вверх) =====
            AddNavButton(pnSidebarBottom, "Выход");

            AddNavButton(pnSidebarMenu, "Настройки стоимости");
            AddNavButton(pnSidebarMenu, "Клиенты");
            AddNavButton(pnSidebarMenu, "Заказы");
            AddNavButton(pnSidebarMenu, "Главная");

            // ===== Страницы =====
            BuildHomePage();
            BuildOrdersPage();
            BuildClientsPage();
            BuildCostSettingsPage();

            this->ResumeLayout(true);
            this->PerformLayout();
        }

        void AddNavButton(Panel^ parent, String^ text)
        {
            Button^ btn = gcnew Button();
            btn->Text = text;
            StyleNavButton(btn);
            btn->Click += gcnew EventHandler(this, &AdminWindow::OnNavClick);

            navButtons[text] = btn;
            parent->Controls->Add(btn);
        }

        Panel^ CreatePage(String^ key)
        {
            Panel^ page = gcnew Panel();
            page->Dock = DockStyle::Fill;
            page->Visible = false;
            page->BackColor = C_Back();

            pnContent->Controls->Add(page);
            pages[key] = page;
            return page;
        }

        // =========================== Pages ===========================
        void BuildHomePage()
        {
            Panel^ page = CreatePage("Главная");

            Label^ h = gcnew Label();
            h->Text = "Дашборд";
            h->Font = F_Title();
            h->ForeColor = C_TextDark();
            h->AutoSize = true;
            h->Location = Point(30, 24);
            page->Controls->Add(h);

            // Cards
            Panel^ card1 = MakeCard(30, 80, 320, 140);
            Panel^ card2 = MakeCard(370, 80, 320, 140);
            Panel^ card3 = MakeCard(710, 80, 320, 140);

            page->Controls->Add(card1);
            page->Controls->Add(card2);
            page->Controls->Add(card3);

            // card 1: orders
            Label^ t1 = gcnew Label();
            t1->Text = "Заказы";
            t1->Font = F_Bold();
            t1->ForeColor = C_TextDark();
            t1->AutoSize = true;
            t1->Location = Point(16, 16);
            card1->Controls->Add(t1);

            lblStatOrders = gcnew Label();
            lblStatOrders->Text = "0";
            lblStatOrders->Font = gcnew Drawing::Font(L"Segoe UI", 24, FontStyle::Bold);
            lblStatOrders->ForeColor = C_TextDark();
            lblStatOrders->AutoSize = true;
            lblStatOrders->Location = Point(16, 52);
            card1->Controls->Add(lblStatOrders);

            // card 2: revenue
            Label^ t2 = gcnew Label();
            t2->Text = "Выручка";
            t2->Font = F_Bold();
            t2->ForeColor = C_TextDark();
            t2->AutoSize = true;
            t2->Location = Point(16, 16);
            card2->Controls->Add(t2);

            lblStatRevenue = gcnew Label();
            lblStatRevenue->Text = "0 ₽";
            lblStatRevenue->Font = gcnew Drawing::Font(L"Segoe UI", 24, FontStyle::Bold);
            lblStatRevenue->ForeColor = C_TextDark();
            lblStatRevenue->AutoSize = true;
            lblStatRevenue->Location = Point(16, 52);
            card2->Controls->Add(lblStatRevenue);

            // card 3: active
            Label^ t3 = gcnew Label();
            t3->Text = "Активные заявки";
            t3->Font = F_Bold();
            t3->ForeColor = C_TextDark();
            t3->AutoSize = true;
            t3->Location = Point(16, 16);
            card3->Controls->Add(t3);

            lblStatActive = gcnew Label();
            lblStatActive->Text = "0";
            lblStatActive->Font = gcnew Drawing::Font(L"Segoe UI", 24, FontStyle::Bold);
            lblStatActive->ForeColor = C_TextDark();
            lblStatActive->AutoSize = true;
            lblStatActive->Location = Point(16, 52);
            card3->Controls->Add(lblStatActive);

            // Hint card
            Panel^ hint = MakeCard(30, 250, 1000, 180);
            page->Controls->Add(hint);

            Label^ ht = gcnew Label();
            ht->Text = "Подсказка";
            ht->Font = F_Bold();
            ht->ForeColor = C_TextDark();
            ht->AutoSize = true;
            ht->Location = Point(16, 16);
            hint->Controls->Add(ht);

            Label^ hb = gcnew Label();
            hb->Text = "Статистика обновляется из таблицы заказов (страница «Заказы»).";
            hb->Font = F_Body();
            hb->ForeColor = C_TextDark();
            hb->AutoSize = true;
            hb->Location = Point(16, 50);
            hint->Controls->Add(hb);
        }

        void BuildOrdersPage()
        {
            Panel^ page = CreatePage("Заказы");

            Panel^ card = MakeCard(30, 30, 1350, 720);
            card->Anchor = AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right;
            page->Controls->Add(card);

            // layout: grid + right tools
            TableLayoutPanel^ lay = gcnew TableLayoutPanel();
            lay->Dock = DockStyle::Fill;
            lay->ColumnCount = 2;
            lay->RowCount = 1;
            lay->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 75.0f));
            lay->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 25.0f));
            card->Controls->Add(lay);

            // grid
            dgvOrders = gcnew DataGridView();
            StyleGrid(dgvOrders);
            dgvOrders->ReadOnly = false; // статус будем менять через UI, но grid оставим read-only на ячейки
            dgvOrders->ReadOnly = true;
            dgvOrders->DataSource = AppStorage::Orders();
            dgvOrders->SelectionChanged += gcnew EventHandler(this, &AdminWindow::OnOrderSelectionChanged);
            lay->Controls->Add(dgvOrders, 0, 0);

            // tools
            Panel^ tools = gcnew Panel();
            tools->Dock = DockStyle::Fill;
            tools->Padding = System::Windows::Forms::Padding(14);
            lay->Controls->Add(tools, 1, 0);

            Label^ t = gcnew Label();
            t->Text = "Управление";
            t->Font = F_Title();
            t->ForeColor = C_TextDark();
            t->AutoSize = true;
            t->Location = Point(0, 0);
            tools->Controls->Add(t);

            Label^ l1 = gcnew Label();
            l1->Text = "Статус заказа";
            l1->Font = F_Bold();
            l1->ForeColor = C_TextDark();
            l1->AutoSize = true;
            l1->Location = Point(0, 60);
            tools->Controls->Add(l1);

            cbStatus = gcnew ComboBox();
            cbStatus->DropDownStyle = ComboBoxStyle::DropDownList;
            cbStatus->Font = F_Body();
            cbStatus->Width = 260;
            cbStatus->Location = Point(0, 90);
            cbStatus->Items->AddRange(gcnew array<Object^>{
                "Создан", "В обработке", "В пути", "Доставлен", "Отменен"
            });
            cbStatus->SelectedIndex = 0;
            tools->Controls->Add(cbStatus);

            btnApplyStatus = gcnew Button();
            btnApplyStatus->Text = "Применить к выбранному";
            btnApplyStatus->Width = 260;
            btnApplyStatus->Location = Point(0, 140);
            StylePrimaryButton(btnApplyStatus);
            btnApplyStatus->Click += gcnew EventHandler(this, &AdminWindow::OnApplyStatus);
            tools->Controls->Add(btnApplyStatus);

            btnDeleteOrder = gcnew Button();
            btnDeleteOrder->Text = "Удалить выбранный";
            btnDeleteOrder->Width = 260;
            btnDeleteOrder->Location = Point(0, 190);
            StylePrimaryButton(btnDeleteOrder);
            btnDeleteOrder->BackColor = Color::FromArgb(180, 60, 60);
            btnDeleteOrder->Click += gcnew EventHandler(this, &AdminWindow::OnDeleteOrder);
            tools->Controls->Add(btnDeleteOrder);

            Label^ h = gcnew Label();
            h->Text = "Примечание: статусы сохраняются в logistics_storage.xml";
            h->Font = F_Body();
            h->ForeColor = Color::FromArgb(90, 90, 90);
            h->AutoSize = false;
            h->Width = 260;
            h->Height = 60;
            h->Location = Point(0, 250);
            tools->Controls->Add(h);
        }

        void BuildClientsPage()
        {
            Panel^ page = CreatePage("Клиенты");

            Panel^ card = MakeCard(30, 30, 1350, 720);
            card->Anchor = AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right;
            page->Controls->Add(card);

            TableLayoutPanel^ lay = gcnew TableLayoutPanel();
            lay->Dock = DockStyle::Fill;
            lay->ColumnCount = 2;
            lay->RowCount = 2;
            lay->RowStyles->Add(gcnew RowStyle(SizeType::Absolute, 56.0f));
            lay->RowStyles->Add(gcnew RowStyle(SizeType::Percent, 100.0f));
            lay->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 40.0f));
            lay->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 60.0f));
            card->Controls->Add(lay);

            // header row
            Panel^ header = gcnew Panel();
            header->Dock = DockStyle::Fill;
            header->Padding = System::Windows::Forms::Padding(14, 10, 14, 10);
            lay->Controls->Add(header, 0, 0);
            lay->SetColumnSpan(header, 2);

            Label^ t = gcnew Label();
            t->Text = "Клиенты и история заказов";
            t->Font = F_Title();
            t->ForeColor = C_TextDark();
            t->AutoSize = true;
            t->Location = Point(0, 10);
            header->Controls->Add(t);

            btnSyncClients = gcnew Button();
            btnSyncClients->Text = "Синхронизировать из заказов";
            btnSyncClients->Width = 280;
            btnSyncClients->Location = Point(820, 8);
            StylePrimaryButton(btnSyncClients);
            btnSyncClients->Click += gcnew EventHandler(this, &AdminWindow::OnSyncClients);
            header->Controls->Add(btnSyncClients);

            // left grid: clients
            dgvClients = gcnew DataGridView();
            StyleGrid(dgvClients);
            dgvClients->DataSource = AppStorage::Clients();
            dgvClients->SelectionChanged += gcnew EventHandler(this, &AdminWindow::OnClientSelectionChanged);
            lay->Controls->Add(dgvClients, 0, 1);

            // right grid: orders of client
            dgvClientOrders = gcnew DataGridView();
            StyleGrid(dgvClientOrders);

            clientOrdersView = gcnew DataView(AppStorage::Orders());
            clientOrdersView->RowFilter = "1=0"; // пока пусто
            dgvClientOrders->DataSource = clientOrdersView;

            lay->Controls->Add(dgvClientOrders, 1, 1);
        }

        void BuildCostSettingsPage()
        {
            Panel^ page = CreatePage("Настройки стоимости");

            Panel^ card = MakeCard(30, 30, 1350, 720);
            card->Anchor = AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right;
            page->Controls->Add(card);

            Panel^ wrap = gcnew Panel();
            wrap->Dock = DockStyle::Fill;
            wrap->AutoScroll = true;
            wrap->Padding = System::Windows::Forms::Padding(18);
            card->Controls->Add(wrap);

            Label^ t = gcnew Label();
            t->Text = "Настройки стоимости";
            t->Font = F_Title();
            t->ForeColor = C_TextDark();
            t->AutoSize = true;
            t->Location = Point(0, 0);
            wrap->Controls->Add(t);

            Label^ hint = gcnew Label();
            hint->Text = "Эти значения сохраняются в logistics_storage.xml и могут использоваться в расчётах (ClientWindow).";
            hint->Font = F_Body();
            hint->ForeColor = Color::FromArgb(90, 90, 90);
            hint->AutoSize = true;
            hint->Location = Point(0, 36);
            wrap->Controls->Add(hint);

            // Grid-like editor
            int y = 80;

            AddSettingRow(wrap, y, "InsurancePercent", "Страховка (% от объявленной стоимости)", 0, 100, 0.5, 1);
            AddSettingRow(wrap, y, "ExpressMultiplier", "Экспресс (множитель)", 1.0, 5.0, 0.05, 2);
            AddSettingRow(wrap, y, "FragileSurcharge", "Хрупкий груз (надбавка, руб)", 0, 50000, 50, 0);
            AddSettingRow(wrap, y, "PickupFee", "Забор от адреса (руб)", 0, 50000, 50, 0);
            AddSettingRow(wrap, y, "DeliveryFee", "Доставка до адреса (руб)", 0, 50000, 50, 0);
            AddSettingRow(wrap, y, "PackagingFee", "Упаковка (руб)", 0, 50000, 50, 0);

            AddSettingRow(wrap, y, "CargoCoef_Standard", "Коэффициент груза: стандарт", 0.1, 5.0, 0.05, 2);
            AddSettingRow(wrap, y, "CargoCoef_Documents", "Коэффициент груза: документы", 0.1, 5.0, 0.05, 2);
            AddSettingRow(wrap, y, "CargoCoef_Oversize", "Коэффициент груза: крупногабарит", 0.1, 5.0, 0.05, 2);

            btnSaveSettings = gcnew Button();
            btnSaveSettings->Text = "Сохранить настройки";
            btnSaveSettings->Width = 260;
            btnSaveSettings->Location = Point(0, y + 10);
            StylePrimaryButton(btnSaveSettings);
            btnSaveSettings->Click += gcnew EventHandler(this, &AdminWindow::OnSaveSettings);
            wrap->Controls->Add(btnSaveSettings);
        }

        // Добавляет строку редактирования настройки в блок "Настройки стоимости"
        void AddSettingRow(Panel^ wrap, int% y, String^ key, String^ title,
            double min, double max, double step, int decimals)
        {
            Label^ l = gcnew Label();
            l->Text = title;
            l->Font = F_Body();
            l->ForeColor = C_TextDark();
            l->AutoSize = false;
            l->Width = 520;
            l->Height = 28;
            l->Location = Point(0, y + 6);
            wrap->Controls->Add(l);

            NumericUpDown^ n = gcnew NumericUpDown();
            n->Font = F_Body();
            n->Width = 200;
            n->Location = Point(540, y);
            n->Minimum = System::Decimal(min);
            n->Maximum = System::Decimal(max);
            n->Increment = System::Decimal(step);
            n->DecimalPlaces = decimals;

            double current = AppStorage::GetSetting(key, (min + max) * 0.5);
            // Ограничим на случай кривых значений в XML
            if (current < min) current = min;
            if (current > max) current = max;

            n->Value = System::Decimal(current);

            wrap->Controls->Add(n);
            settingEditors[key] = n;

            y += 46;
        }


        // =========================== Navigation ===========================
        void ShowPage(String^ key)
        {
            if (key == "Выход")
            {
                this->Close();
                return;
            }

            for each (System::Collections::Generic::KeyValuePair<String^, Panel^> kv in pages) kv.Value->Visible = false;

            for each (System::Collections::Generic::KeyValuePair<String^, Button^> kv in navButtons)
            {
                kv.Value->BackColor = C_Side();
                kv.Value->ForeColor = Color::FromArgb(220, 220, 220);
            }

            if (pages->ContainsKey(key)) pages[key]->Visible = true;

            if (navButtons->ContainsKey(key))
            {
                navButtons[key]->BackColor = C_SideHover();
                navButtons[key]->ForeColor = Color::White;
            }

            lblTitle->Text = key;

            if (key == "Главная") RefreshDashboard();
        }

        void RefreshDashboard()
        {
            DataTable^ t = AppStorage::Orders();

            int total = t->Rows->Count;
            int active = 0;
            double revenue = 0.0;

            for each (DataRow ^ r in t->Rows)
            {
                if (r->RowState == DataRowState::Deleted) continue;

                String^ st = r["Status"] != nullptr ? Convert::ToString(r["Status"]) : "";
                if (!String::Equals(st, "Доставлен") && !String::Equals(st, "Отменен"))
                    active++;

                try { revenue += Convert::ToDouble(r["TotalCost"]); }
                catch (...) {}
            }

            if (lblStatOrders) lblStatOrders->Text = total.ToString();
            if (lblStatActive) lblStatActive->Text = active.ToString();
            if (lblStatRevenue) lblStatRevenue->Text = String::Format("{0:N0} ₽", revenue);
        }

        // =========================== Events ===========================
        System::Void OnNavClick(System::Object^ sender, System::EventArgs^ e)
        {
            Button^ btn = dynamic_cast<Button^>(sender);
            if (btn != nullptr) ShowPage(btn->Text);
        }

        int SelectedOrderId()
        {
            if (dgvOrders == nullptr || dgvOrders->SelectedRows->Count == 0) return -1;
            DataGridViewRow^ row = dgvOrders->SelectedRows[0];
            if (row == nullptr) return -1;

            Object^ v = row->Cells["Id"]->Value;
            if (v == nullptr) return -1;

            try { return Convert::ToInt32(v); }
            catch (...) { return -1; }
        }

        DataRow^ FindOrderRow(int id)
        {
            if (id <= 0) return nullptr;
            DataRow^ r = AppStorage::Orders()->Rows->Find(id);
            return r;
        }

        System::Void OnOrderSelectionChanged(System::Object^, System::EventArgs^)
        {
            int id = SelectedOrderId();
            DataRow^ r = FindOrderRow(id);
            if (r == nullptr) return;

            String^ st = r["Status"] != nullptr ? Convert::ToString(r["Status"]) : "Создан";
            int idx = cbStatus->Items->IndexOf(st);
            if (idx >= 0) cbStatus->SelectedIndex = idx;
        }

        System::Void OnApplyStatus(System::Object^, System::EventArgs^)
        {
            int id = SelectedOrderId();
            DataRow^ r = FindOrderRow(id);
            if (r == nullptr)
            {
                MessageBox::Show("Выберите заказ в таблице.", "Заказы", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            r["Status"] = cbStatus->SelectedItem != nullptr ? cbStatus->SelectedItem->ToString() : "Создан";
            r["UpdatedAt"] = DateTime::Now;
            AppStorage::Save();

            RefreshDashboard();
        }

        System::Void OnDeleteOrder(System::Object^, System::EventArgs^)
        {
            int id = SelectedOrderId();
            DataRow^ r = FindOrderRow(id);
            if (r == nullptr)
            {
                MessageBox::Show("Выберите заказ в таблице.", "Заказы", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            auto res = MessageBox::Show("Удалить выбранный заказ?", "Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
            if (res != System::Windows::Forms::DialogResult::Yes) return;

            r->Delete();
            AppStorage::Orders()->AcceptChanges();
            AppStorage::Save();

            RefreshDashboard();
        }

        System::Void OnSyncClients(System::Object^, System::EventArgs^)
        {
            DataTable^ orders = AppStorage::Orders();
            DataTable^ clients = AppStorage::Clients();
            for each (DataRow ^ r in orders->Rows)
            {
                if (r->RowState == DataRowState::Deleted) continue;

                String^ phone = r["ClientPhone"] != nullptr ? Convert::ToString(r["ClientPhone"]) : "";
                String^ name = r["ClientName"] != nullptr ? Convert::ToString(r["ClientName"]) : "";

                if (String::IsNullOrWhiteSpace(phone)) continue;
                // Проверим, есть ли уже такой клиент
                bool exists = false;
                for each (DataRow ^ c in clients->Rows)
                {
                    if (c->RowState == DataRowState::Deleted) continue;

                    String^ p = c["Phone"] != nullptr ? Convert::ToString(c["Phone"]) : "";
                    if (String::Equals(p, phone))
                    {
                        exists = true;
                        // Обновим имя, если пустое
                        String^ n = c["Name"] != nullptr ? Convert::ToString(c["Name"]) : "";
                        if (String::IsNullOrWhiteSpace(n) && !String::IsNullOrWhiteSpace(name))
                            c["Name"] = name;
                        break;
                    }
                }

                if (!exists)
                {
                    DataRow^ c = clients->NewRow();
                    c["Name"] = name;
                    c["Phone"] = phone;
                    c["Email"] = "";
                    clients->Rows->Add(c);
                }
            }

            AppStorage::Save();
            MessageBox::Show("Синхронизация выполнена.", "Клиенты", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        System::Void OnClientSelectionChanged(System::Object^, System::EventArgs^)
        {
            if (dgvClients == nullptr || dgvClients->SelectedRows->Count == 0)
            {
                if (clientOrdersView) clientOrdersView->RowFilter = "1=0";
                return;
            }

            DataGridViewRow^ row = dgvClients->SelectedRows[0];
            if (row == nullptr) return;

            Object^ v = row->Cells["Phone"]->Value;
            String^ phone = v != nullptr ? v->ToString() : "";

            if (String::IsNullOrWhiteSpace(phone))
            {
                clientOrdersView->RowFilter = "1=0";
                return;
            }

            // RowFilter: экранируем одинарные кавычки
            String^ safe = phone->Replace("'", "''");
            clientOrdersView->RowFilter = String::Format("ClientPhone = '{0}'", safe);
        }

        System::Void OnSaveSettings(System::Object^, System::EventArgs^)
        {
            for each (System::Collections::Generic::KeyValuePair<String^, NumericUpDown^> kv in settingEditors)
            {
                String^ key = kv.Key;
                NumericUpDown^ n = kv.Value;
                double value = Convert::ToDouble(n->Value);
                AppStorage::UpdateSetting(key, value);
            }

            MessageBox::Show("Настройки сохранены.", "Настройки стоимости", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    };
}
