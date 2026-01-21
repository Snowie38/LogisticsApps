#pragma once

namespace LogisticsApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public ref class AdminWindow : public System::Windows::Forms::Form
	{
	public:
		AdminWindow(void)
		{
			InitializeComponent();
			BuildAdminUI();
			ShowPage(L"Главная");
		}

	protected:
		~AdminWindow()
		{
			if (components) delete components;
		}

	private:
		System::ComponentModel::Container^ components;

		// ===== UI элементы =====
		Panel^ pnSidebar;
		Panel^ pnTop;
		Panel^ pnContent;
		Label^ lblTitle;

		// Страницы 
		Dictionary<String^, Panel^>^ pages;
		Dictionary<String^, Button^>^ navButtons;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// AdminWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1500, 820);
			this->Name = L"AdminWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Администрирование";
			this->ResumeLayout(false);
		}
#pragma endregion

		// ====== МЕНЮ ======
		void BuildAdminUI()
		{
			this->SuspendLayout();
			this->BackColor = Color::FromArgb(240, 242, 245);

			pages = gcnew Dictionary<String^, Panel^>();
			navButtons = gcnew Dictionary<String^, Button^>();

			// ===== Sidebar =====
			pnSidebar = gcnew Panel();
			pnSidebar->Dock = DockStyle::Left;
			pnSidebar->Width = 260;
			pnSidebar->BackColor = Color::FromArgb(32, 36, 48);

			// Внутренние зоны сайдбара
			Panel^ pnSidebarTop = gcnew Panel();
			pnSidebarTop->Dock = DockStyle::Top;
			pnSidebarTop->Height = 90;
			pnSidebarTop->BackColor = pnSidebar->BackColor;

			Panel^ pnSidebarBottom = gcnew Panel();
			pnSidebarBottom->Dock = DockStyle::Bottom;
			pnSidebarBottom->Height = 90;
			pnSidebarBottom->BackColor = pnSidebar->BackColor;

			Panel^ pnSidebarMenu = gcnew Panel();
			pnSidebarMenu->Dock = DockStyle::Fill;
			pnSidebarMenu->BackColor = pnSidebar->BackColor;

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

			// ===== Main container справа =====
			Panel^ pnMain = gcnew Panel();
			pnMain->Dock = DockStyle::Fill;
			pnMain->BackColor = Color::FromArgb(240, 242, 245);

			// Top bar
			pnTop = gcnew Panel();
			pnTop->Dock = DockStyle::Top;
			pnTop->Height = 60;
			pnTop->BackColor = Color::White;

			lblTitle = gcnew Label();
			lblTitle->Dock = DockStyle::Fill;
			lblTitle->TextAlign = ContentAlignment::MiddleLeft;
			lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
			lblTitle->ForeColor = Color::FromArgb(40, 40, 40);
			lblTitle->Padding = System::Windows::Forms::Padding(16, 0, 0, 0);
			lblTitle->Text = L"Админ-панель";
			pnTop->Controls->Add(lblTitle);

			// Content
			pnContent = gcnew Panel();
			pnContent->Dock = DockStyle::Fill;
			pnContent->BackColor = Color::FromArgb(240, 242, 245);

			pnMain->Controls->Add(pnContent);
			pnMain->Controls->Add(pnTop);

			this->Controls->Add(pnMain);
			this->Controls->Add(pnSidebar);

			AddNavButton(pnSidebarMenu, L"Настройки");
			AddNavButton(pnSidebarMenu, L"Опции / Услуги");
			AddNavButton(pnSidebarMenu, L"Тарифы / Расстояния");
			AddNavButton(pnSidebarMenu, L"Клиенты");
			AddNavButton(pnSidebarMenu, L"Заказы");
			AddNavButton(pnSidebarMenu, L"Главная");


			// ===== Страницы =====
			CreatePage(L"Главная", L"Здесь будет дашборд: статистика заказов, выручка, активные заявки.");
			CreatePage(L"Заказы", L"Здесь будет таблица заказов (DataGridView) и смена статусов.");
			CreatePage(L"Клиенты", L"Здесь будет список клиентов и история заказов.");
			CreatePage(L"Тарифы / Расстояния", L"Здесь будет редактирование расстояний и базовых тарифов.");
			CreatePage(L"Опции / Услуги", L"Здесь будут цены на доп. опции: упаковка, документы, паллетирование...");
			CreatePage(L"Настройки", L"Здесь будут коэффициенты: страховка %, экспресс-множитель, характер груза и т.д.");

			this->ResumeLayout(true);
			this->PerformLayout();
		}

		void AddNavButton(Panel^ parent, String^ text)
		{
			Button^ btn = gcnew Button();
			btn->Dock = DockStyle::Top;
			btn->Height = 48;
			btn->FlatStyle = FlatStyle::Flat;
			btn->FlatAppearance->BorderSize = 0;
			btn->TextAlign = ContentAlignment::MiddleLeft;
			btn->Padding = System::Windows::Forms::Padding(16, 0, 0, 0);
			btn->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Regular);
			btn->ForeColor = Color::FromArgb(220, 220, 220);
			btn->BackColor = Color::FromArgb(32, 36, 48);
			btn->Text = text;
			btn->Cursor = Cursors::Hand;

			btn->Click += gcnew EventHandler(this, &AdminWindow::OnNavClick);

			navButtons[text] = btn;
			parent->Controls->Add(btn); // без SetChildIndex
		}

		void CreatePage(String^ key, String^ hint)
		{
			Panel^ page = gcnew Panel();
			page->Dock = DockStyle::Fill;
			page->Visible = false;
			page->BackColor = Color::FromArgb(240, 242, 245);

			Panel^ card = gcnew Panel();
			card->BackColor = Color::White;
			card->Size = System::Drawing::Size(900, 240);
			card->Location = System::Drawing::Point(30, 30);
			card->BorderStyle = BorderStyle::FixedSingle;

			Label^ h1 = gcnew Label();
			h1->AutoSize = false;
			h1->Dock = DockStyle::Top;
			h1->Height = 50;
			h1->TextAlign = ContentAlignment::MiddleLeft;
			h1->Padding = System::Windows::Forms::Padding(16, 0, 0, 0);
			h1->Font = gcnew Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
			h1->Text = key;

			Label^ h2 = gcnew Label();
			h2->AutoSize = false;
			h2->Dock = DockStyle::Fill;
			h2->TextAlign = ContentAlignment::TopLeft;
			h2->Padding = System::Windows::Forms::Padding(16, 10, 16, 16);
			h2->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Regular);
			h2->Text = hint;

			card->Controls->Add(h2);
			card->Controls->Add(h1);

			page->Controls->Add(card);
			pnContent->Controls->Add(page);

			pages[key] = page;
		}

		void ShowPage(String^ key)
		{
			// Выход
			if (key == L"Выход")
			{
				this->Close();
				return;
			}

			// спрятать все страницы
			for each (auto kv in pages)
				kv.Value->Visible = false;

			// сбросить подсветку кнопок
			for each (auto kv in navButtons)
			{
				kv.Value->BackColor = Color::FromArgb(32, 36, 48);
				kv.Value->ForeColor = Color::FromArgb(220, 220, 220);
			}

			// показать нужную страницу
			if (pages->ContainsKey(key))
				pages[key]->Visible = true;

			// подсветить кнопку
			if (navButtons->ContainsKey(key))
			{
				navButtons[key]->BackColor = Color::FromArgb(55, 63, 85);
				navButtons[key]->ForeColor = Color::White;
			}

			lblTitle->Text = key;
		}

		System::Void OnNavClick(System::Object^ sender, System::EventArgs^ e)
		{
			Button^ btn = dynamic_cast<Button^>(sender);
			if (btn != nullptr)
				ShowPage(btn->Text);
		}
	};
}
