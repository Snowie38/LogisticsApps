#pragma once
// AdminWindow.h (no designer) — единый стиль, без лямбд, без auto, без HashSet.
// Вкладки:
//  - Главная (дашборд)
//  - Заказы (таблица + статус/удаление)
//  - Клиенты (Одна таблица: Фамилия/Имя/Отчество/Паспорт/Телефон отправителя)
//  - Настройки стоимости (редактирование Settings из AppStorage)
//
// ВАЖНО:
//  - Никаких лямбда-выражений (C++/CLI часто ломается)
//  - Никаких «₽» и прочих спорных символов (используем "руб")
//  - Паддинги и Dock/Anchor, чтобы ничего не "съезжало"

#include "AppStorage.h"

namespace LogisticsApp {

    using namespace System;
    using namespace System::Collections::Generic;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Windows::Forms;

    public ref class AdminWindow : public Form
    {
    public:
        AdminWindow()
        {
            InitializeComponent();
            AppStorage::Init();
            BuildUI();
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

        Panel^ pnSidebar;
        Panel^ pnTop;
        Panel^ pnContent;
        Label^ lblTitle;

        Dictionary<String^, Panel^>^ pages;
        Dictionary<String^, Button^>^ navButtons;

        // Dashboard
        Label^ lblStatOrders;
        Label^ lblStatRevenue;
        Label^ lblStatActive;

        // Orders
        DataGridView^ dgvOrders;
        ComboBox^ cbStatus;
        Button^ btnApplyStatus;
        Button^ btnDeleteOrder;

        // Clients (ONE grid)
        DataGridView^ dgvClients;
        DataTable^ dtClientsView;

        // Settings
        Dictionary<String^, NumericUpDown^>^ settingEditors;
        Button^ btnSaveSettings;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->SuspendLayout();
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1500, 820);
            this->MinimumSize = System::Drawing::Size(1100, 700);
            this->Name = L"AdminWindow";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Администрирование";
            this->ResumeLayout(false);
        }
#pragma endregion

        // ===== theme helpers =====
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

        void StyleGridBase(DataGridView^ g)
        {
            g->Dock = DockStyle::Fill;
            g->BackgroundColor = Color::White;
            g->BorderStyle = BorderStyle::None;
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
            g->AutoSizeRowsMode = DataGridViewAutoSizeRowsMode::None;
            g->RowTemplate->Height = 28;
            g->ScrollBars = ScrollBars::Both;
        }

        Panel^ MakeCard()
        {
            Panel^ card = gcnew Panel();
            card->Dock = DockStyle::Fill;
            card->BackColor = Color::White;
            card->BorderStyle = BorderStyle::FixedSingle;
            return card;
        }

        Panel^ CreatePage(String^ key)
        {
            Panel^ page = gcnew Panel();
            page->Dock = DockStyle::Fill;
            page->Visible = false;
            page->BackColor = C_Back();
            page->Padding = System::Windows::Forms::Padding(24); // <-- паддинг страницы
            pnContent->Controls->Add(page);
            pages[key] = page;
            return page;
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

        Panel^ MakeStatCard(String^ title, Label^% valueLabel)
        {
            Panel^ card = MakeCard();
            card->Padding = System::Windows::Forms::Padding(16);

            Label^ t = gcnew Label();
            t->Text = title;
            t->Font = F_Bold();
            t->ForeColor = C_TextDark();
            t->Dock = DockStyle::Top;
            t->Height = 24;
            card->Controls->Add(t);

            valueLabel = gcnew Label();
            valueLabel->Text = "0";
            valueLabel->Font = gcnew Drawing::Font(L"Segoe UI", 24, FontStyle::Bold);
            valueLabel->ForeColor = C_TextDark();
            valueLabel->Dock = DockStyle::Fill;
            valueLabel->TextAlign = ContentAlignment::MiddleLeft;
            card->Controls->Add(valueLabel);

            return card;
        }

        // ===== Build UI =====
        void BuildUI()
        {
            this->SuspendLayout();
            this->BackColor = C_Back();

            pages = gcnew Dictionary<String^, Panel^>();
            navButtons = gcnew Dictionary<String^, Button^>();
            settingEditors = gcnew Dictionary<String^, NumericUpDown^>();

            // Sidebar
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

            // Main
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
            lblTitle->Padding = System::Windows::Forms::Padding(16, 0, 0, 0); // <-- паддинг заголовка
            lblTitle->Text = L"Админ-панель";
            pnTop->Controls->Add(lblTitle);

            pnContent = gcnew Panel();
            pnContent->Dock = DockStyle::Fill;
            pnContent->BackColor = C_Back();

            pnMain->Controls->Add(pnContent);
            pnMain->Controls->Add(pnTop);

            this->Controls->Add(pnMain);
            this->Controls->Add(pnSidebar);

            // Nav (сверху вниз — добавляем в обратном порядке для DockStyle::Top)
            AddNavButton(pnSidebarBottom, "Выход");
            AddNavButton(pnSidebarMenu, "Настройки стоимости");
            AddNavButton(pnSidebarMenu, "Клиенты");
            AddNavButton(pnSidebarMenu, "Заказы");
            AddNavButton(pnSidebarMenu, "Главная");

            // Pages
            BuildHomePage();
            BuildOrdersPage();
            BuildClientsPage();
            BuildCostSettingsPage();

            this->ResumeLayout(true);
            this->PerformLayout();
        }

        // ===== Pages =====
        void BuildHomePage()
        {
            Panel^ page = CreatePage("Главная");

            TableLayoutPanel^ root = gcnew TableLayoutPanel();
            root->Dock = DockStyle::Fill;
            root->RowCount = 3;
            root->ColumnCount = 3;
            root->RowStyles->Add(gcnew RowStyle(SizeType::Absolute, 60));
            root->RowStyles->Add(gcnew RowStyle(SizeType::Absolute, 170));
            root->RowStyles->Add(gcnew RowStyle(SizeType::Percent, 100));
            root->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 33.33f));
            root->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 33.33f));
            root->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 33.33f));
            page->Controls->Add(root);

            Label^ h = gcnew Label();
            h->Text = "Дашборд";
            h->Font = F_Title();
            h->ForeColor = C_TextDark();
            h->Dock = DockStyle::Fill;
            h->TextAlign = ContentAlignment::MiddleLeft;
            root->Controls->Add(h, 0, 0);
            root->SetColumnSpan(h, 3);

            Label^ v1 = nullptr; Label^ v2 = nullptr; Label^ v3 = nullptr;
            Panel^ c1 = MakeStatCard("Заказы", v1);
            Panel^ c2 = MakeStatCard("Выручка", v2);
            Panel^ c3 = MakeStatCard("Активные заявки", v3);

            root->Controls->Add(c1, 0, 1);
            root->Controls->Add(c2, 1, 1);
            root->Controls->Add(c3, 2, 1);

            lblStatOrders = v1;
            lblStatRevenue = v2;
            lblStatActive = v3;

            Panel^ hint = MakeCard();
            hint->Padding = System::Windows::Forms::Padding(16);

            Label^ ht = gcnew Label();
            ht->Text = "Подсказка";
            ht->Font = F_Bold();
            ht->ForeColor = C_TextDark();
            ht->Dock = DockStyle::Top;
            ht->Height = 24;
            hint->Controls->Add(ht);

            Label^ hb = gcnew Label();
            hb->Text = "Статистика строится по таблице заказов (страница «Заказы»).";
            hb->Font = F_Body();
            hb->ForeColor = Color::FromArgb(90, 90, 90);
            hb->Dock = DockStyle::Fill;
            hint->Controls->Add(hb);

            root->Controls->Add(hint, 0, 2);
            root->SetColumnSpan(hint, 3);
        }

        void BuildOrdersPage()
        {
            Panel^ page = CreatePage("Заказы");

            Panel^ card = MakeCard();
            card->Padding = System::Windows::Forms::Padding(12); // <-- паддинг карточки
            page->Controls->Add(card);

            TableLayoutPanel^ lay = gcnew TableLayoutPanel();
            lay->Dock = DockStyle::Fill;
            lay->ColumnCount = 2;
            lay->RowCount = 1;
            lay->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 76.0f));
            lay->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 24.0f));
            card->Controls->Add(lay);

            dgvOrders = gcnew DataGridView();
            StyleGridBase(dgvOrders);
            dgvOrders->AutoGenerateColumns = true;
            dgvOrders->DataSource = AppStorage::Orders();
            dgvOrders->SelectionChanged += gcnew EventHandler(this, &AdminWindow::OnOrderSelectionChanged);
            dgvOrders->DataBindingComplete += gcnew DataGridViewBindingCompleteEventHandler(this, &AdminWindow::OnOrdersDataBindingComplete);
            lay->Controls->Add(dgvOrders, 0, 0);

            Panel^ tools = gcnew Panel();
            tools->Dock = DockStyle::Fill;
            tools->Padding = System::Windows::Forms::Padding(14); // <-- паддинг инструментов
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
            cbStatus->Items->AddRange(gcnew array<Object^>{ "Создан", "В обработке", "В пути", "Доставлен", "Отменен" });
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

            ConfigureOrdersGrid(); // <-- фиксируем колонки и ширины
        }

        void OnOrdersDataBindingComplete(System::Object^ sender, DataGridViewBindingCompleteEventArgs^ e)
        {
            // После привязки данных столбцы уже созданы — можно настроить отображение
            ConfigureOrdersGrid();
        }

        bool IsNameInList(String^ name, array<String^>^ list)
        {
            if (list == nullptr) return false;
            for each (String ^ s in list)
            {
                if (String::Equals(s, name)) return true;
            }
            return false;
        }

        void TrySetHeader(String^ name, String^ header)
        {
            if (dgvOrders == nullptr) return;
            if (!dgvOrders->Columns->Contains(name)) return;
            dgvOrders->Columns[name]->HeaderText = header;
        }

        void TrySetWidth(String^ name, int width)
        {
            if (dgvOrders == nullptr) return;
            if (!dgvOrders->Columns->Contains(name)) return;
            DataGridViewColumn^ c = dgvOrders->Columns[name];
            c->Width = width;
        }

        void TrySetFormat(String^ name, String^ format)
        {
            if (dgvOrders == nullptr) return;
            if (!dgvOrders->Columns->Contains(name)) return;
            dgvOrders->Columns[name]->DefaultCellStyle->Format = format;
        }

        void ApplyOrdersDisplayOrder()
        {
            if (dgvOrders == nullptr) return;

            array<String^>^ preferred = gcnew array<String^>{
                "Id", "CreatedAt", "UpdatedAt", "Status",
                    "SenderType", "SenderName", "SenderPhone",
                    "SenderInn", "SenderOrgName", "SenderOpf", "SenderKpp",
                    "SenderPassSeries", "SenderPassNumber", "SenderPassDate",
                    "RecipientType", "RecipientName", "RecipientPhone",
                    "RecipientInn", "RecipientOrgName", "RecipientOpf", "RecipientKpp",
                    "RecipientPassSeries", "RecipientPassNumber", "RecipientPassDate",
                    "CityFrom", "FromAddress", "PickupFromAddress",
                    "CityTo", "ToAddress", "DeliveryToAddress",
                    "DistanceKm", "CargoType", "CargoTypeIndex",
                    "WeightKg", "VolumeM3", "LengthM", "DeclaredValue",
                    "DeliveryType",
                    "OptProtectPack", "OptPallet", "OptFloorDelivery", "OptDocsA", "OptDocsB",
                    "BaseCost", "OptionsCost", "InsuranceCost", "TotalCost"
            };

            int idx = 0;
            for each (String ^ col in preferred)
            {
                if (dgvOrders->Columns->Contains(col))
                {
                    dgvOrders->Columns[col]->DisplayIndex = idx;
                    idx++;
                }
            }

            // Остальные столбцы — в конец
            for each (DataGridViewColumn ^ c in dgvOrders->Columns)
            {
                if (!IsNameInList(c->Name, preferred))
                {
                    c->DisplayIndex = idx;
                    idx++;
                }
            }
        }

        void ConfigureOrdersGrid()
        {
            if (dgvOrders == nullptr) return;
            if (dgvOrders->Columns == nullptr) return;

            // Показываем ВСЕ столбцы, которые есть в таблице Orders
            dgvOrders->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::DisplayedCells;
            dgvOrders->ScrollBars = ScrollBars::Both;

            for each (DataGridViewColumn ^ c in dgvOrders->Columns)
            {
                c->Visible = true;
                c->SortMode = DataGridViewColumnSortMode::Automatic;
                c->MinimumWidth = 60;
            }

            // Читаемые заголовки (не обязательно, но сильно помогает)
            TrySetHeader("Id", "ID");
            TrySetHeader("CreatedAt", "Создан");
            TrySetHeader("UpdatedAt", "Обновлен");
            TrySetHeader("Status", "Статус");

            TrySetHeader("SenderType", "Тип отправителя");
            TrySetHeader("SenderName", "ФИО отправителя");
            TrySetHeader("SenderPhone", "Телефон отправителя");
            TrySetHeader("SenderInn", "ИНН отправителя");
            TrySetHeader("SenderOrgName", "Орг. название отправителя");
            TrySetHeader("SenderOpf", "ОПФ отправителя");
            TrySetHeader("SenderKpp", "КПП отправителя");
            TrySetHeader("SenderPassSeries", "Паспорт серия (отпр.)");
            TrySetHeader("SenderPassNumber", "Паспорт номер (отпр.)");
            TrySetHeader("SenderPassDate", "Дата паспорта (отпр.)");

            TrySetHeader("RecipientType", "Тип получателя");
            TrySetHeader("RecipientName", "ФИО получателя");
            TrySetHeader("RecipientPhone", "Телефон получателя");
            TrySetHeader("RecipientInn", "ИНН получателя");
            TrySetHeader("RecipientOrgName", "Орг. название получателя");
            TrySetHeader("RecipientOpf", "ОПФ получателя");
            TrySetHeader("RecipientKpp", "КПП получателя");
            TrySetHeader("RecipientPassSeries", "Паспорт серия (пол.)");
            TrySetHeader("RecipientPassNumber", "Паспорт номер (пол.)");
            TrySetHeader("RecipientPassDate", "Дата паспорта (пол.)");

            TrySetHeader("CityFrom", "Город отправления");
            TrySetHeader("FromAddress", "Адрес забора");
            TrySetHeader("PickupFromAddress", "Забор с адреса");

            TrySetHeader("CityTo", "Город доставки");
            TrySetHeader("ToAddress", "Адрес доставки");
            TrySetHeader("DeliveryToAddress", "Доставка до адреса");

            TrySetHeader("DistanceKm", "Км");
            TrySetHeader("CargoType", "Тип груза");
            TrySetHeader("CargoTypeIndex", "Индекс типа груза");
            TrySetHeader("WeightKg", "Вес (кг)");
            TrySetHeader("VolumeM3", "Объем (м3)");
            TrySetHeader("LengthM", "Длина (м)");
            TrySetHeader("DeclaredValue", "Оценочная стоимость");
            TrySetHeader("DeliveryType", "Тип доставки");

            TrySetHeader("OptProtectPack", "Защитная упаковка");
            TrySetHeader("OptPallet", "Паллет");
            TrySetHeader("OptFloorDelivery", "Подъем на этаж");
            TrySetHeader("OptDocsA", "Документы A");
            TrySetHeader("OptDocsB", "Документы B");

            TrySetHeader("BaseCost", "База, руб");
            TrySetHeader("OptionsCost", "Опции, руб");
            TrySetHeader("InsuranceCost", "Страхование, руб");
            TrySetHeader("TotalCost", "Итого, руб");

            // Форматы
            TrySetFormat("CreatedAt", "dd.MM.yyyy HH:mm");
            TrySetFormat("UpdatedAt", "dd.MM.yyyy HH:mm");
            TrySetFormat("SenderPassDate", "dd.MM.yyyy");
            TrySetFormat("RecipientPassDate", "dd.MM.yyyy");

            TrySetFormat("WeightKg", "N2");
            TrySetFormat("VolumeM3", "N3");
            TrySetFormat("LengthM", "N2");
            TrySetFormat("DeclaredValue", "N0");
            TrySetFormat("BaseCost", "N0");
            TrySetFormat("OptionsCost", "N0");
            TrySetFormat("InsuranceCost", "N0");
            TrySetFormat("TotalCost", "N0");

            // Чуть более удобные ширины для ключевых полей
            TrySetWidth("SenderName", 180);
            TrySetWidth("RecipientName", 180);
            TrySetWidth("SenderOrgName", 220);
            TrySetWidth("RecipientOrgName", 220);
            TrySetWidth("FromAddress", 220);
            TrySetWidth("ToAddress", 220);

            ApplyOrdersDisplayOrder();
        }

        void ShowOrderColumn(String^ name, String^ header, int width)
        {
            if (dgvOrders == nullptr) return;
            if (!dgvOrders->Columns->Contains(name)) return;

            DataGridViewColumn^ c = dgvOrders->Columns[name];
            c->Visible = true;
            c->HeaderText = header;
            c->Width = width;
            c->MinimumWidth = 50;
        }

        void BuildClientsPage()
        {
            Panel^ page = CreatePage("Клиенты");

            Panel^ card = MakeCard();
            card->Padding = System::Windows::Forms::Padding(12);
            page->Controls->Add(card);

            TableLayoutPanel^ lay = gcnew TableLayoutPanel();
            lay->Dock = DockStyle::Fill;
            lay->RowCount = 2;
            lay->ColumnCount = 1;
            lay->RowStyles->Add(gcnew RowStyle(SizeType::Absolute, 56.0f));
            lay->RowStyles->Add(gcnew RowStyle(SizeType::Percent, 100.0f));
            card->Controls->Add(lay);

            Panel^ header = gcnew Panel();
            header->Dock = DockStyle::Fill;
            header->Padding = System::Windows::Forms::Padding(14, 10, 14, 10);
            lay->Controls->Add(header, 0, 0);

            Label^ t = gcnew Label();
            t->Text = "Клиенты (по отправителю)";
            t->Font = F_Title();
            t->ForeColor = C_TextDark();
            t->AutoSize = true;
            t->Location = Point(0, 10);
            header->Controls->Add(t);

            dgvClients = gcnew DataGridView();
            StyleGridBase(dgvClients);
            dgvClients->AutoGenerateColumns = true;
            lay->Controls->Add(dgvClients, 0, 1);

            // Витрина клиентов
            dtClientsView = gcnew DataTable("ClientsView");
            dtClientsView->Columns->Add("LastName", String::typeid);
            dtClientsView->Columns->Add("FirstName", String::typeid);
            dtClientsView->Columns->Add("MiddleName", String::typeid);
            dtClientsView->Columns->Add("Passport", String::typeid); // серия номер
            dtClientsView->Columns->Add("SenderPhone", String::typeid);

            dgvClients->DataSource = dtClientsView;
            dgvClients->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        }

        void RefreshClientsFromOrders()
        {
            if (dtClientsView == nullptr) return;

            dtClientsView->Rows->Clear();

            DataTable^ orders = AppStorage::Orders();
            Dictionary<String^, bool>^ seen = gcnew Dictionary<String^, bool>();

            for each (DataRow ^ r in orders->Rows)
            {
                if (r->RowState == DataRowState::Deleted) continue;

                String^ phone = (r->Table->Columns->Contains("SenderPhone") && r["SenderPhone"] != nullptr)
                    ? Convert::ToString(r["SenderPhone"])
                    : "";

                if (String::IsNullOrWhiteSpace(phone)) continue;
                if (seen->ContainsKey(phone)) continue;
                seen[phone] = true;

                String^ last = "";
                String^ first = "";
                String^ mid = "";

                // Если у тебя ФИО хранится одной строкой SenderName — аккуратно разложим по частям.
                if (r->Table->Columns->Contains("SenderLastName")) last = Convert::ToString(r["SenderLastName"]);
                if (r->Table->Columns->Contains("SenderFirstName")) first = Convert::ToString(r["SenderFirstName"]);
                if (r->Table->Columns->Contains("SenderMiddleName")) mid = Convert::ToString(r["SenderMiddleName"]);

                if (String::IsNullOrWhiteSpace(last) && r->Table->Columns->Contains("SenderName"))
                {
                    String^ fio = Convert::ToString(r["SenderName"]);
                    array<String^>^ parts = fio->Split(gcnew array<wchar_t>{' '}, StringSplitOptions::RemoveEmptyEntries);
                    if (parts->Length > 0) last = parts[0];
                    if (parts->Length > 1) first = parts[1];
                    if (parts->Length > 2) mid = parts[2];
                }

                String^ ps = (r->Table->Columns->Contains("SenderPassportSeries") && r["SenderPassportSeries"] != nullptr)
                    ? Convert::ToString(r["SenderPassportSeries"])
                    : "";
                String^ pn = (r->Table->Columns->Contains("SenderPassportNumber") && r["SenderPassportNumber"] != nullptr)
                    ? Convert::ToString(r["SenderPassportNumber"])
                    : "";
                String^ passport = (ps + " " + pn)->Trim();

                DataRow^ nr = dtClientsView->NewRow();
                nr["LastName"] = last;
                nr["FirstName"] = first;
                nr["MiddleName"] = mid;
                nr["Passport"] = passport;
                nr["SenderPhone"] = phone;
                dtClientsView->Rows->Add(nr);
            }
        }

        void AddSettingRow(Panel^ wrap, String^ key, String^ title, double min, double max, double step, int decimals, int% y)
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
            n->Width = 220;
            n->Location = Point(540, y);
            n->Minimum = Decimal(min);
            n->Maximum = Decimal(max);
            n->Increment = Decimal(step);
            n->DecimalPlaces = decimals;
            n->Value = Decimal(AppStorage::GetSetting(key, min));
            wrap->Controls->Add(n);

            settingEditors[key] = n;
            y += 46;
        }

        void BuildCostSettingsPage()
        {
            Panel^ page = CreatePage("Настройки стоимости");

            Panel^ card = MakeCard();
            card->Padding = System::Windows::Forms::Padding(12);
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

            int y = 60;

            AddSettingRow(wrap, "RatePerKm", "Тариф за 1 км", 0, 1000, 1, 0, y);
            AddSettingRow(wrap, "RatePerKg", "Тариф за 1 кг", 0, 1000, 1, 0, y);
            AddSettingRow(wrap, "RatePerM3", "Тариф за 1 м^3", 0, 100000, 5, 0, y);
            AddSettingRow(wrap, "RatePerM", "Тариф за 1 метр длины", 0, 10000, 1, 0, y);

            AddSettingRow(wrap, "ExpressMultiplier", "Экспресс (множитель)", 1.0, 10.0, 0.05, 2, y);
            AddSettingRow(wrap, "InsurancePercent", "Страховка (% от объявленной стоимости)", 0, 100, 0.1, 1, y);

            AddSettingRow(wrap, "PickupFee", "Забор от адреса (руб)", 0, 50000, 10, 0, y);
            AddSettingRow(wrap, "DeliveryFee", "Доставка до адреса (руб)", 0, 50000, 10, 0, y);
            AddSettingRow(wrap, "ProtectPackFee", "Защитная упаковка (руб)", 0, 50000, 10, 0, y);
            AddSettingRow(wrap, "PalletFee", "Палетирование (руб)", 0, 50000, 10, 0, y);
            AddSettingRow(wrap, "FloorDeliveryFee", "Доставка на этаж (руб)", 0, 50000, 10, 0, y);
            AddSettingRow(wrap, "DocsFeeA", "Документы A (руб)", 0, 50000, 10, 0, y);
            AddSettingRow(wrap, "DocsFeeB", "Документы B (руб)", 0, 50000, 10, 0, y);

            AddSettingRow(wrap, "CargoCoef_0", "Груз: обычный (коэф.)", 0.1, 10.0, 0.05, 2, y);
            AddSettingRow(wrap, "CargoCoef_1", "Груз: хрупкое (коэф.)", 0.1, 10.0, 0.05, 2, y);
            AddSettingRow(wrap, "CargoCoef_2", "Груз: документы (коэф.)", 0.1, 10.0, 0.05, 2, y);
            AddSettingRow(wrap, "CargoCoef_3", "Груз: крупногабарит (коэф.)", 0.1, 10.0, 0.05, 2, y);
            AddSettingRow(wrap, "CargoCoef_4", "Груз: топливо (коэф.)", 0.1, 10.0, 0.05, 2, y);
            AddSettingRow(wrap, "CargoCoef_5", "Груз: газ (коэф.)", 0.1, 10.0, 0.05, 2, y);
            AddSettingRow(wrap, "CargoCoef_6", "Груз: радиоактивные (коэф.)", 0.1, 10.0, 0.05, 2, y);

            btnSaveSettings = gcnew Button();
            btnSaveSettings->Text = "Сохранить настройки";
            btnSaveSettings->Width = 260;
            btnSaveSettings->Location = Point(0, y + 10);
            StylePrimaryButton(btnSaveSettings);
            btnSaveSettings->Click += gcnew EventHandler(this, &AdminWindow::OnSaveSettings);
            wrap->Controls->Add(btnSaveSettings);
        }

        // ===== Navigation =====
        void ShowPage(String^ key)
        {
            if (key == "Выход")
            {
                this->Close();
                return;
            }

            // hide all
            for each (KeyValuePair<String^, Panel^> kv in pages)
                kv.Value->Visible = false;

            // reset nav
            for each (KeyValuePair<String^, Button^> kv in navButtons)
            {
                kv.Value->BackColor = C_Side();
                kv.Value->ForeColor = Color::FromArgb(220, 220, 220);
            }

            if (pages->ContainsKey(key))
                pages[key]->Visible = true;

            if (navButtons->ContainsKey(key))
            {
                navButtons[key]->BackColor = C_SideHover();
                navButtons[key]->ForeColor = Color::White;
            }

            lblTitle->Text = key;

            if (key == "Главная") RefreshDashboard();
            if (key == "Клиенты") RefreshClientsFromOrders();
            if (key == "Заказы") ConfigureOrdersGrid();
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

            if (lblStatOrders)  lblStatOrders->Text = total.ToString();
            if (lblStatActive)  lblStatActive->Text = active.ToString();
            if (lblStatRevenue) lblStatRevenue->Text = String::Format("{0:N0} руб", revenue);
        }

        // ===== Events =====
        System::Void OnNavClick(System::Object^ sender, System::EventArgs^)
        {
            Button^ btn = dynamic_cast<Button^>(sender);
            if (btn != nullptr) ShowPage(btn->Text);
        }

        int SelectedOrderId()
        {
            if (dgvOrders == nullptr) return -1;
            if (dgvOrders->SelectedRows->Count == 0) return -1;

            DataGridViewRow^ row = dgvOrders->SelectedRows[0];
            if (row == nullptr) return -1;

            if (!dgvOrders->Columns->Contains("Id")) return -1;
            Object^ v = row->Cells["Id"]->Value;
            if (v == nullptr) return -1;

            try { return Convert::ToInt32(v); }
            catch (...) { return -1; }
        }

        DataRow^ FindOrderRow(int id)
        {
            if (id <= 0) return nullptr;
            // Для Rows->Find() нужен PrimaryKey. Он у нас должен быть в AppStorage.
            try { return AppStorage::Orders()->Rows->Find(id); }
            catch (...) { return nullptr; }
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
            if (r->Table->Columns->Contains("UpdatedAt"))
                r["UpdatedAt"] = DateTime::Now;

            AppStorage::Save();
            RefreshDashboard();
            ConfigureOrdersGrid();
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

            System::Windows::Forms::DialogResult res =
                MessageBox::Show("Удалить выбранный заказ?", "Подтверждение",
                    MessageBoxButtons::YesNo, MessageBoxIcon::Warning);

            if (res != System::Windows::Forms::DialogResult::Yes) return;

            r->Delete();
            AppStorage::Save();
            RefreshDashboard();
            ConfigureOrdersGrid();
        }

        System::Void OnSaveSettings(System::Object^, System::EventArgs^)
        {
            for each (KeyValuePair<String^, NumericUpDown^> kv in settingEditors)
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
