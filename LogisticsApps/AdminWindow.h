#pragma once

// AdminWindow без дизайнера. Структура:
// - Главная: дашборд
// - Заказы: DataGridView + статус/удаление
// - Клиенты: база клиентов + история заказов
// - Настройки стоимости: редактирование коэффициентов/цен
//
// ВАЖНО: без лямбд (C++/CLI часто ругается), без символа RUBLE (чтобы не было проблем с кодовой страницей).

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

        // Clients
        DataGridView^ dgvClients;
        DataGridView^ dgvClientOrders;
        DataView^ clientOrdersView;

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

        // ===== colors/fonts =====
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

        void StyleGrid(DataGridView^ g)
        {
            g->Dock = DockStyle::Fill;
            g->BackgroundColor = Color::White;
            g->BorderStyle = BorderStyle::None;
            g->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::None;
            g->AutoSizeRowsMode = DataGridViewAutoSizeRowsMode::None;
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


        void ShowColumn(DataGridView^ grid, String^ colName, String^ header, int displayIndex, int width)
        {
            if (grid == nullptr) return;
            if (!grid->Columns->Contains(colName)) return;

            DataGridViewColumn^ c = grid->Columns[colName];
            c->Visible = true;
            c->HeaderText = header;
            c->DisplayIndex = displayIndex;
            c->AutoSizeMode = DataGridViewAutoSizeColumnMode::None;
            c->Width = width;
            c->MinimumWidth = Math::Min(width, 60);
        }

        void HideAllColumns(DataGridView^ grid)
        {
            if (grid == nullptr) return;
            for each (DataGridViewColumn ^ c in grid->Columns)
            {
                c->Visible = false;
                c->MinimumWidth = 60;
            }
        }

        void ConfigureOrdersGrid()
        {
            if (dgvOrders == nullptr) return;

            HideAllColumns(dgvOrders);

            // Ключевые колонки (компактный набор)
            ShowColumn(dgvOrders, "Id", "ID", 0, 50);
            ShowColumn(dgvOrders, "CreatedAt", "Дата", 1, 120);
            ShowColumn(dgvOrders, "Status", "Статус", 2, 120);
            ShowColumn(dgvOrders, "CityFrom", "Откуда", 3, 120);
            ShowColumn(dgvOrders, "CityTo", "Куда", 4, 120);
            ShowColumn(dgvOrders, "DistanceKm", "Км", 5, 60);
            ShowColumn(dgvOrders, "CargoType", "Груз", 6, 120);
            ShowColumn(dgvOrders, "WeightKg", "Вес, кг", 7, 80);
            ShowColumn(dgvOrders, "TotalCost", "�?того, руб", 8, 110);
            ShowColumn(dgvOrders, "RecipientName", "Получатель", 9, 160);
            ShowColumn(dgvOrders, "RecipientPhone", "Телефон", 10, 120);

            // Форматы
            if (dgvOrders->Columns->Contains("TotalCost"))
                dgvOrders->Columns["TotalCost"]->DefaultCellStyle->Format = "N0";

            if (dgvOrders->Columns->Contains("CreatedAt"))
                dgvOrders->Columns["CreatedAt"]->DefaultCellStyle->Format = "dd.MM.yyyy HH:mm";

            // Перенос заголовков и горизонтальный скролл (если окно узкое)
            dgvOrders->ColumnHeadersDefaultCellStyle->WrapMode = DataGridViewTriState::True;
            dgvOrders->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            dgvOrders->ScrollBars = ScrollBars::Both;
        }

        void ConfigureClientsGrid()
        {
            if (dgvClients == nullptr) return;

            HideAllColumns(dgvClients);
            ShowColumn(dgvClients, "Id", "ID", 0, 50);
            ShowColumn(dgvClients, "Name", "�?мя", 1, 160);
            ShowColumn(dgvClients, "Phone", "Телефон", 2, 120);
            dgvClients->ScrollBars = ScrollBars::Both;
        }

        void ConfigureClientOrdersGrid()
        {
            if (dgvClientOrders == nullptr) return;

            HideAllColumns(dgvClientOrders);
            ShowColumn(dgvClientOrders, "Id", "ID", 0, 50);
            ShowColumn(dgvClientOrders, "CreatedAt", "Дата", 1, 120);
            ShowColumn(dgvClientOrders, "Status", "Статус", 2, 120);
            ShowColumn(dgvClientOrders, "CityFrom", "Откуда", 3, 120);
            ShowColumn(dgvClientOrders, "CityTo", "Куда", 4, 120);
            ShowColumn(dgvClientOrders, "TotalCost", "�?того, руб", 5, 110);

            if (dgvClientOrders->Columns->Contains("TotalCost"))
                dgvClientOrders->Columns["TotalCost"]->DefaultCellStyle->Format = "N0";

            if (dgvClientOrders->Columns->Contains("CreatedAt"))
                dgvClientOrders->Columns["CreatedAt"]->DefaultCellStyle->Format = "dd.MM.yyyy HH:mm";

            dgvClientOrders->ScrollBars = ScrollBars::Both;
        }

        Panel^ MakeCardDocked()
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
            page->Padding = System::Windows::Forms::Padding(24);
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
            Panel^ card = MakeCardDocked();
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

        // ===== build UI =====
        void BuildAdminUI()
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

            // Nav
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

        // ===== pages =====
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

            Panel^ hint = MakeCardDocked();
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

            Panel^ card = MakeCardDocked();
            page->Controls->Add(card);

            TableLayoutPanel^ lay = gcnew TableLayoutPanel();
            lay->Dock = DockStyle::Fill;
            lay->ColumnCount = 2;
            lay->RowCount = 1;
            lay->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 76.0f));
            lay->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 24.0f));
            card->Controls->Add(lay);

            dgvOrders = gcnew DataGridView();
            StyleGrid(dgvOrders);
            dgvOrders->DataSource = AppStorage::Orders();
            ConfigureOrdersGrid();
            dgvOrders->SelectionChanged += gcnew EventHandler(this, &AdminWindow::OnOrderSelectionChanged);
            lay->Controls->Add(dgvOrders, 0, 0);

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
        }

        void BuildClientsPage()
        {
            Panel^ page = CreatePage("�������");

            Panel^ card = MakeCardDocked();
            page->Controls->Add(card);

            TableLayoutPanel^ lay = gcnew TableLayoutPanel();
            lay->Dock = DockStyle::Fill;
            lay->ColumnCount = 1;
            lay->RowCount = 2;
            lay->RowStyles->Add(gcnew RowStyle(SizeType::Absolute, 56.0f));
            lay->RowStyles->Add(gcnew RowStyle(SizeType::Percent, 100.0f));
            card->Controls->Add(lay);

            Panel^ header = gcnew Panel();
            header->Dock = DockStyle::Fill;
            header->Padding = System::Windows::Forms::Padding(14, 10, 14, 10);
            lay->Controls->Add(header, 0, 0);

            Label^ t = gcnew Label();
            t->Text = "���� ��������";
            t->Font = F_Title();
            t->ForeColor = C_TextDark();
            t->AutoSize = true;
            t->Location = Point(0, 10);
            header->Controls->Add(t);

            dgvClients = gcnew DataGridView();
            StyleGrid(dgvClients);
            dgvClients->Dock = DockStyle::Fill;
            dgvClients->DataSource = AppStorage::Clients();
            ConfigureClientsGrid();
            lay->Controls->Add(dgvClients, 0, 1);
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

            Panel^ card = MakeCardDocked();
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

        // ===== navigation / stats =====
        void ShowPage(String^ key)
        {
            if (key == "Выход") { this->Close(); return; }

            for each (auto kv in pages) kv.Value->Visible = false;
            for each (auto kv in navButtons) { kv.Value->BackColor = C_Side(); kv.Value->ForeColor = Color::FromArgb(220, 220, 220); }

            if (pages->ContainsKey(key)) pages[key]->Visible = true;
            if (navButtons->ContainsKey(key)) { navButtons[key]->BackColor = C_SideHover(); navButtons[key]->ForeColor = Color::White; }

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
            if (lblStatRevenue) lblStatRevenue->Text = String::Format("{0:N0} руб", revenue);
        }

        // ===== events =====
        System::Void OnNavClick(System::Object^ sender, System::EventArgs^)
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
            return AppStorage::Orders()->Rows->Find(id);
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

            System::Windows::Forms::DialogResult res = MessageBox::Show(
                "Удалить выбранный заказ?", "Подтверждение",
                MessageBoxButtons::YesNo, MessageBoxIcon::Warning);

            if (res != System::Windows::Forms::DialogResult::Yes) return;

            r->Delete();
            AppStorage::Orders()->AcceptChanges();
            AppStorage::Save();
            RefreshDashboard();
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
            if (String::IsNullOrWhiteSpace(phone)) { clientOrdersView->RowFilter = "1=0"; return; }

            String^ safe = phone->Replace("'", "''");
            clientOrdersView->RowFilter = String::Format("RecipientPhone = '{0}'", safe);
        }

        System::Void OnSaveSettings(System::Object^, System::EventArgs^)
        {
            for each (auto kv in settingEditors)
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
