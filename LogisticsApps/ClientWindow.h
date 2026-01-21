#pragma once
#include "DistanceTable.h"
#include <msclr/marshal_cppstd.h>
#include "LoginWindow.h"
#include "UITheme.h"

namespace LogisticsApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Globalization;

	public ref class ClientWindow : public System::Windows::Forms::Form
	{
	public:
		ClientWindow(void)
		{
			InitializeComponent();
			UITheme::Apply(this);
		}


	protected:
		~ClientWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Panel^ pn_cargo_info;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ tb_nCost;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::ComboBox^ cb_type_cargo;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Panel^ pn_distant_info;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::TextBox^ tb_where;
	private: System::Windows::Forms::TextBox^ tb_whereFrom;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::TextBox^ tb_length;
	private: System::Windows::Forms::TextBox^ tb_weight;
	private: System::Windows::Forms::TextBox^ tb_volume;
	private: System::Windows::Forms::CheckBox^ chb_from_adress;
	private: System::Windows::Forms::TextBox^ tb_where_adress;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::CheckBox^ chb_where_adress;
	private: System::Windows::Forms::TextBox^ tb_from_adress;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Label^ label22;
	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::Label^ label29;
	private: System::Windows::Forms::Label^ label28;
	private: System::Windows::Forms::CheckBox^ checkBox5;
	private: System::Windows::Forms::CheckBox^ checkBox4;
	private: System::Windows::Forms::Label^ label27;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::Panel^ pn_result;
	private: System::Windows::Forms::Label^ label30;
	private: System::Windows::Forms::GroupBox^ gbDeliveryType;
	private: System::Windows::Forms::RadioButton^ rbExpress;
	private: System::Windows::Forms::RadioButton^ rbStandard;
	private: System::Windows::Forms::Label^ lblInsuranceCost;
	private: System::Windows::Forms::Label^ lblOptionsCost;
	private: System::Windows::Forms::Label^ lblWeightCost;
	private: System::Windows::Forms::Label^ lblDistanceCost;
	private: System::Windows::Forms::Label^ lb_COST;
	private: System::Windows::Forms::Button^ btn_on_login_win;
	protected:
	protected:
	protected:
	protected:
	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->pn_distant_info = (gcnew System::Windows::Forms::Panel());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->tb_from_adress = (gcnew System::Windows::Forms::TextBox());
			this->chb_where_adress = (gcnew System::Windows::Forms::CheckBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->tb_where_adress = (gcnew System::Windows::Forms::TextBox());
			this->chb_from_adress = (gcnew System::Windows::Forms::CheckBox());
			this->tb_where = (gcnew System::Windows::Forms::TextBox());
			this->tb_whereFrom = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pn_cargo_info = (gcnew System::Windows::Forms::Panel());
			this->tb_length = (gcnew System::Windows::Forms::TextBox());
			this->tb_weight = (gcnew System::Windows::Forms::TextBox());
			this->tb_volume = (gcnew System::Windows::Forms::TextBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->cb_type_cargo = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->tb_nCost = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pn_result = (gcnew System::Windows::Forms::Panel());
			this->btn_on_login_win = (gcnew System::Windows::Forms::Button());
			this->lb_COST = (gcnew System::Windows::Forms::Label());
			this->lblWeightCost = (gcnew System::Windows::Forms::Label());
			this->lblInsuranceCost = (gcnew System::Windows::Forms::Label());
			this->lblOptionsCost = (gcnew System::Windows::Forms::Label());
			this->lblDistanceCost = (gcnew System::Windows::Forms::Label());
			this->gbDeliveryType = (gcnew System::Windows::Forms::GroupBox());
			this->rbExpress = (gcnew System::Windows::Forms::RadioButton());
			this->rbStandard = (gcnew System::Windows::Forms::RadioButton());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->panel4->SuspendLayout();
			this->pn_distant_info->SuspendLayout();
			this->panel3->SuspendLayout();
			this->pn_cargo_info->SuspendLayout();
			this->panel2->SuspendLayout();
			this->pn_result->SuspendLayout();
			this->gbDeliveryType->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->AutoSize = true;
			this->panel1->BackColor = System::Drawing::Color::Gainsboro;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->panel4);
			this->panel1->Controls->Add(this->pn_distant_info);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->pn_cargo_info);
			this->panel1->Location = System::Drawing::Point(19, 19);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(884, 1091);
			this->panel1->TabIndex = 0;
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::WhiteSmoke;
			this->panel4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel4->Controls->Add(this->label29);
			this->panel4->Controls->Add(this->label28);
			this->panel4->Controls->Add(this->checkBox5);
			this->panel4->Controls->Add(this->checkBox4);
			this->panel4->Controls->Add(this->label27);
			this->panel4->Controls->Add(this->label26);
			this->panel4->Controls->Add(this->checkBox3);
			this->panel4->Controls->Add(this->label25);
			this->panel4->Controls->Add(this->label24);
			this->panel4->Controls->Add(this->label23);
			this->panel4->Controls->Add(this->checkBox2);
			this->panel4->Controls->Add(this->checkBox1);
			this->panel4->Controls->Add(this->label22);
			this->panel4->Controls->Add(this->label19);
			this->panel4->Location = System::Drawing::Point(15, 858);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(843, 222);
			this->panel4->TabIndex = 1;
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(660, 99);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(50, 16);
			this->label29->TabIndex = 26;
			this->label29->Text = L"(+100₽)";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(725, 70);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(50, 16);
			this->label28->TabIndex = 25;
			this->label28->Text = L"(+150₽)";
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(487, 96);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(167, 20);
			this->checkBox5->TabIndex = 24;
			this->checkBox5->Text = L"Возврат документов";
			this->checkBox5->UseVisualStyleBackColor = true;
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(487, 69);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(232, 20);
			this->checkBox4->TabIndex = 23;
			this->checkBox4->Text = L"Сопроводительные документы";
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// label27
			// 
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label27->Location = System::Drawing::Point(483, 42);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(153, 24);
			this->label27->TabIndex = 22;
			this->label27->Text = L"Документы:";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(175, 146);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(36, 16);
			this->label26->TabIndex = 21;
			this->label26->Text = L"(+0₽)";
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(24, 145);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(145, 20);
			this->checkBox3->TabIndex = 20;
			this->checkBox3->Text = L"Доставка на этаж";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// label25
			// 
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label25->Location = System::Drawing::Point(20, 118);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(153, 24);
			this->label25->TabIndex = 19;
			this->label25->Text = L"Доставка:";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(160, 96);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(50, 16);
			this->label24->TabIndex = 18;
			this->label24->Text = L"(+600₽)";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(330, 69);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(50, 16);
			this->label23->TabIndex = 16;
			this->label23->Text = L"(+510₽)";
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(23, 95);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(134, 20);
			this->checkBox2->TabIndex = 17;
			this->checkBox2->Text = L"Палетирование";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(23, 69);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(301, 20);
			this->checkBox1->TabIndex = 1;
			this->checkBox1->Text = L"Защитная транспортировачная упаковка";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// label22
			// 
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label22->Location = System::Drawing::Point(20, 42);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(153, 24);
			this->label22->TabIndex = 16;
			this->label22->Text = L"Упаковка: ";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label19->Location = System::Drawing::Point(13, 11);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(265, 25);
			this->label19->TabIndex = 15;
			this->label19->Text = L"Дополнительные опции:";
			// 
			// pn_distant_info
			// 
			this->pn_distant_info->BackColor = System::Drawing::Color::WhiteSmoke;
			this->pn_distant_info->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pn_distant_info->Controls->Add(this->label21);
			this->pn_distant_info->Controls->Add(this->label20);
			this->pn_distant_info->Controls->Add(this->tb_from_adress);
			this->pn_distant_info->Controls->Add(this->chb_where_adress);
			this->pn_distant_info->Controls->Add(this->panel3);
			this->pn_distant_info->Controls->Add(this->tb_where_adress);
			this->pn_distant_info->Controls->Add(this->chb_from_adress);
			this->pn_distant_info->Controls->Add(this->tb_where);
			this->pn_distant_info->Controls->Add(this->tb_whereFrom);
			this->pn_distant_info->Controls->Add(this->label16);
			this->pn_distant_info->Controls->Add(this->label15);
			this->pn_distant_info->Controls->Add(this->label14);
			this->pn_distant_info->Controls->Add(this->label13);
			this->pn_distant_info->Controls->Add(this->label12);
			this->pn_distant_info->Location = System::Drawing::Point(15, 458);
			this->pn_distant_info->Name = L"pn_distant_info";
			this->pn_distant_info->Size = System::Drawing::Size(843, 375);
			this->pn_distant_info->TabIndex = 9;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(749, 144);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(50, 16);
			this->label21->TabIndex = 15;
			this->label21->Text = L"(+510₽)";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(222, 144);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(50, 16);
			this->label20->TabIndex = 1;
			this->label20->Text = L"(+710₽)";
			// 
			// tb_from_adress
			// 
			this->tb_from_adress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_from_adress->Location = System::Drawing::Point(531, 170);
			this->tb_from_adress->Multiline = true;
			this->tb_from_adress->Name = L"tb_from_adress";
			this->tb_from_adress->Size = System::Drawing::Size(212, 98);
			this->tb_from_adress->TabIndex = 1;
			this->tb_from_adress->Text = L"Россия, Москва, проспект Андропова, 34, 43";
			this->tb_from_adress->Visible = false;
			this->tb_from_adress->TextChanged += gcnew System::EventHandler(this, &ClientWindow::tb_from_adress_TextChanged);
			// 
			// chb_where_adress
			// 
			this->chb_where_adress->AutoSize = true;
			this->chb_where_adress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->chb_where_adress->Location = System::Drawing::Point(531, 140);
			this->chb_where_adress->Name = L"chb_where_adress";
			this->chb_where_adress->Size = System::Drawing::Size(212, 24);
			this->chb_where_adress->TabIndex = 14;
			this->chb_where_adress->Text = L"Доставить по адресу";
			this->chb_where_adress->UseVisualStyleBackColor = true;
			this->chb_where_adress->CheckedChanged += gcnew System::EventHandler(this, &ClientWindow::chb_where_adress_CheckedChanged);
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel3->Controls->Add(this->label17);
			this->panel3->Controls->Add(this->label18);
			this->panel3->Location = System::Drawing::Point(16, 274);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(803, 88);
			this->panel3->TabIndex = 10;
			// 
			// label17
			// 
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label17->Location = System::Drawing::Point(3, 20);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(768, 53);
			this->label17->TabIndex = 9;
			this->label17->Text = L"Стандартная цена доставки состоит из самостоятельной доставки\r\nгруза к месту отпр"
				L"авки и выгрузки.";
			this->label17->Click += gcnew System::EventHandler(this, &ClientWindow::label17_Click);
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label18->ForeColor = System::Drawing::Color::Red;
			this->label18->Location = System::Drawing::Point(3, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(98, 20);
			this->label18->TabIndex = 8;
			this->label18->Text = L"Внимание!";
			// 
			// tb_where_adress
			// 
			this->tb_where_adress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_where_adress->Location = System::Drawing::Point(24, 170);
			this->tb_where_adress->Multiline = true;
			this->tb_where_adress->Name = L"tb_where_adress";
			this->tb_where_adress->Size = System::Drawing::Size(236, 98);
			this->tb_where_adress->TabIndex = 13;
			this->tb_where_adress->Text = L"Россия, Тула, Революции, 17, 55";
			this->tb_where_adress->Visible = false;
			// 
			// chb_from_adress
			// 
			this->chb_from_adress->AutoSize = true;
			this->chb_from_adress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->chb_from_adress->Location = System::Drawing::Point(24, 140);
			this->chb_from_adress->Name = L"chb_from_adress";
			this->chb_from_adress->Size = System::Drawing::Size(192, 24);
			this->chb_from_adress->TabIndex = 1;
			this->chb_from_adress->Text = L"Забрать по адресу";
			this->chb_from_adress->UseVisualStyleBackColor = true;
			this->chb_from_adress->CheckedChanged += gcnew System::EventHandler(this, &ClientWindow::chb_from_adress_CheckedChanged);
			// 
			// tb_where
			// 
			this->tb_where->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_where->Location = System::Drawing::Point(531, 91);
			this->tb_where->Name = L"tb_where";
			this->tb_where->Size = System::Drawing::Size(231, 26);
			this->tb_where->TabIndex = 12;
			this->tb_where->Text = L"Москва";
			// 
			// tb_whereFrom
			// 
			this->tb_whereFrom->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_whereFrom->Location = System::Drawing::Point(24, 91);
			this->tb_whereFrom->Name = L"tb_whereFrom";
			this->tb_whereFrom->ShortcutsEnabled = false;
			this->tb_whereFrom->Size = System::Drawing::Size(210, 26);
			this->tb_whereFrom->TabIndex = 1;
			this->tb_whereFrom->Text = L"Тула";
			// 
			// label16
			// 
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label16->Location = System::Drawing::Point(527, 64);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(153, 24);
			this->label16->TabIndex = 11;
			this->label16->Text = L"Куда:";
			// 
			// label15
			// 
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label15->Location = System::Drawing::Point(20, 64);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(153, 24);
			this->label15->TabIndex = 9;
			this->label15->Text = L"Откуда:";
			// 
			// label14
			// 
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(527, 40);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(153, 24);
			this->label14->TabIndex = 10;
			this->label14->Text = L"Получение";
			// 
			// label13
			// 
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(20, 40);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(153, 24);
			this->label13->TabIndex = 9;
			this->label13->Text = L"Отправка";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(11, 9);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(312, 25);
			this->label12->TabIndex = 9;
			this->label12->Text = L"Город отправки и получения:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(8, 6);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(393, 39);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Рассчитать стоимость";
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Gainsboro;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(11, 66);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(807, 56);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Введите в калькулятор данные о грузе, направление и закажите дополнительные услуг"
				L"и,\r\nчтобы узнать сроки и стоимость перевозки.";
			// 
			// pn_cargo_info
			// 
			this->pn_cargo_info->BackColor = System::Drawing::Color::WhiteSmoke;
			this->pn_cargo_info->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pn_cargo_info->Controls->Add(this->tb_length);
			this->pn_cargo_info->Controls->Add(this->tb_weight);
			this->pn_cargo_info->Controls->Add(this->tb_volume);
			this->pn_cargo_info->Controls->Add(this->panel2);
			this->pn_cargo_info->Controls->Add(this->label9);
			this->pn_cargo_info->Controls->Add(this->cb_type_cargo);
			this->pn_cargo_info->Controls->Add(this->label4);
			this->pn_cargo_info->Controls->Add(this->label8);
			this->pn_cargo_info->Controls->Add(this->tb_nCost);
			this->pn_cargo_info->Controls->Add(this->label7);
			this->pn_cargo_info->Controls->Add(this->label6);
			this->pn_cargo_info->Controls->Add(this->label5);
			this->pn_cargo_info->Controls->Add(this->label1);
			this->pn_cargo_info->Location = System::Drawing::Point(15, 156);
			this->pn_cargo_info->Name = L"pn_cargo_info";
			this->pn_cargo_info->Size = System::Drawing::Size(843, 284);
			this->pn_cargo_info->TabIndex = 0;
			this->pn_cargo_info->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ClientWindow::pn_gruz_Paint);
			// 
			// tb_length
			// 
			this->tb_length->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_length->Location = System::Drawing::Point(531, 76);
			this->tb_length->MaxLength = 10000;
			this->tb_length->Name = L"tb_length";
			this->tb_length->Size = System::Drawing::Size(175, 26);
			this->tb_length->TabIndex = 11;
			this->tb_length->Text = L"5";
			// 
			// tb_weight
			// 
			this->tb_weight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_weight->Location = System::Drawing::Point(16, 76);
			this->tb_weight->MaxLength = 10000;
			this->tb_weight->Name = L"tb_weight";
			this->tb_weight->Size = System::Drawing::Size(175, 26);
			this->tb_weight->TabIndex = 10;
			this->tb_weight->Text = L"5";
			// 
			// tb_volume
			// 
			this->tb_volume->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_volume->Location = System::Drawing::Point(275, 76);
			this->tb_volume->MaxLength = 10000;
			this->tb_volume->Name = L"tb_volume";
			this->tb_volume->Size = System::Drawing::Size(175, 26);
			this->tb_volume->TabIndex = 9;
			this->tb_volume->Text = L"5";
			// 
			// panel2
			// 
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->label11);
			this->panel2->Controls->Add(this->label10);
			this->panel2->Location = System::Drawing::Point(16, 183);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(803, 88);
			this->panel2->TabIndex = 8;
			// 
			// label11
			// 
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(3, 20);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(768, 64);
			this->label11->TabIndex = 9;
			this->label11->Text = L"Согласно п.4 ст.4 Федерального закона от 30.06.2003 № 87-ФЗ «О транспортно-экспед"
				L"иционной деятельности» сотрудник компании обязан провести осмотр груза при приём"
				L"ке!";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->ForeColor = System::Drawing::Color::Red;
			this->label10->Location = System::Drawing::Point(3, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(98, 20);
			this->label10->TabIndex = 8;
			this->label10->Text = L"Внимание!";
			// 
			// label9
			// 
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(13, 144);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(153, 24);
			this->label9->TabIndex = 1;
			this->label9->Text = L"Характер груза:";
			// 
			// cb_type_cargo
			// 
			this->cb_type_cargo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cb_type_cargo->FormattingEnabled = true;
			this->cb_type_cargo->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"Обычный товар", L"Хрупкое", L"Документы",
					L"Крупногабаритный товар", L"Топливо", L"Газ", L"Радиоактивные вещества"
			});
			this->cb_type_cargo->Location = System::Drawing::Point(172, 144);
			this->cb_type_cargo->Name = L"cb_type_cargo";
			this->cb_type_cargo->Size = System::Drawing::Size(180, 28);
			this->cb_type_cargo->TabIndex = 1;
			this->cb_type_cargo->SelectedIndexChanged += gcnew System::EventHandler(this, &ClientWindow::comboBox1_SelectedIndexChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(13, 109);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(199, 25);
			this->label4->TabIndex = 1;
			this->label4->Text = L"Инфомация о грузе";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(405, 145);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(259, 20);
			this->label8->TabIndex = 6;
			this->label8->Text = L"Объявленная стоимость, руб.";
			// 
			// tb_nCost
			// 
			this->tb_nCost->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tb_nCost->Location = System::Drawing::Point(670, 145);
			this->tb_nCost->MaxLength = 1000000;
			this->tb_nCost->Name = L"tb_nCost";
			this->tb_nCost->Size = System::Drawing::Size(149, 26);
			this->tb_nCost->TabIndex = 7;
			this->tb_nCost->Text = L"500";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(527, 41);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(83, 20);
			this->label7->TabIndex = 4;
			this->label7->Text = L"Длина, м";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(271, 41);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(92, 20);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Объем, м³";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(14, 41);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(66, 20);
			this->label5->TabIndex = 1;
			this->label5->Text = L"Вес, кг";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(12, 10);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(198, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Параметры груза:";
			// 
			// pn_result
			// 
			this->pn_result->AutoScroll = true;
			this->pn_result->BackColor = System::Drawing::Color::Gainsboro;
			this->pn_result->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pn_result->Controls->Add(this->btn_on_login_win);
			this->pn_result->Controls->Add(this->lb_COST);
			this->pn_result->Controls->Add(this->lblWeightCost);
			this->pn_result->Controls->Add(this->lblInsuranceCost);
			this->pn_result->Controls->Add(this->lblOptionsCost);
			this->pn_result->Controls->Add(this->lblDistanceCost);
			this->pn_result->Controls->Add(this->gbDeliveryType);
			this->pn_result->Controls->Add(this->label30);
			this->pn_result->Location = System::Drawing::Point(980, 19);
			this->pn_result->Name = L"pn_result";
			this->pn_result->Size = System::Drawing::Size(547, 494);
			this->pn_result->TabIndex = 1;
			// 
			// btn_on_login_win
			// 
			this->btn_on_login_win->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btn_on_login_win->Location = System::Drawing::Point(107, 391);
			this->btn_on_login_win->Name = L"btn_on_login_win";
			this->btn_on_login_win->Size = System::Drawing::Size(359, 69);
			this->btn_on_login_win->TabIndex = 9;
			this->btn_on_login_win->Text = L"Продолжить оформление";
			this->btn_on_login_win->UseVisualStyleBackColor = true;
			this->btn_on_login_win->Click += gcnew System::EventHandler(this, &ClientWindow::btn_on_login_win_Click);
			// 
			// lb_COST
			// 
			this->lb_COST->AutoSize = true;
			this->lb_COST->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lb_COST->Location = System::Drawing::Point(31, 302);
			this->lb_COST->Name = L"lb_COST";
			this->lb_COST->Size = System::Drawing::Size(109, 39);
			this->lb_COST->TabIndex = 8;
			this->lb_COST->Text = L"Итого";
			// 
			// lblWeightCost
			// 
			this->lblWeightCost->AutoSize = true;
			this->lblWeightCost->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lblWeightCost->Location = System::Drawing::Point(33, 234);
			this->lblWeightCost->Name = L"lblWeightCost";
			this->lblWeightCost->Size = System::Drawing::Size(68, 25);
			this->lblWeightCost->TabIndex = 3;
			this->lblWeightCost->Text = L"Масса";
			// 
			// lblInsuranceCost
			// 
			this->lblInsuranceCost->AutoSize = true;
			this->lblInsuranceCost->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lblInsuranceCost->Location = System::Drawing::Point(31, 198);
			this->lblInsuranceCost->Name = L"lblInsuranceCost";
			this->lblInsuranceCost->Size = System::Drawing::Size(132, 25);
			this->lblInsuranceCost->TabIndex = 7;
			this->lblInsuranceCost->Text = L"Страхование";
			// 
			// lblOptionsCost
			// 
			this->lblOptionsCost->AutoSize = true;
			this->lblOptionsCost->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lblOptionsCost->Location = System::Drawing::Point(33, 266);
			this->lblOptionsCost->Name = L"lblOptionsCost";
			this->lblOptionsCost->Size = System::Drawing::Size(112, 25);
			this->lblOptionsCost->TabIndex = 6;
			this->lblOptionsCost->Text = L"Доп опции";
			// 
			// lblDistanceCost
			// 
			this->lblDistanceCost->AutoSize = true;
			this->lblDistanceCost->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lblDistanceCost->Location = System::Drawing::Point(32, 167);
			this->lblDistanceCost->Name = L"lblDistanceCost";
			this->lblDistanceCost->Size = System::Drawing::Size(121, 25);
			this->lblDistanceCost->TabIndex = 2;
			this->lblDistanceCost->Text = L"Расстояние";
			// 
			// gbDeliveryType
			// 
			this->gbDeliveryType->Controls->Add(this->rbExpress);
			this->gbDeliveryType->Controls->Add(this->rbStandard);
			this->gbDeliveryType->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->gbDeliveryType->Location = System::Drawing::Point(31, 56);
			this->gbDeliveryType->Name = L"gbDeliveryType";
			this->gbDeliveryType->Size = System::Drawing::Size(182, 95);
			this->gbDeliveryType->TabIndex = 1;
			this->gbDeliveryType->TabStop = false;
			this->gbDeliveryType->Text = L"Тип доставки:";
			// 
			// rbExpress
			// 
			this->rbExpress->AutoSize = true;
			this->rbExpress->Location = System::Drawing::Point(23, 65);
			this->rbExpress->Name = L"rbExpress";
			this->rbExpress->Size = System::Drawing::Size(109, 24);
			this->rbExpress->TabIndex = 1;
			this->rbExpress->Text = L"Экспресс";
			this->rbExpress->UseVisualStyleBackColor = true;
			this->rbExpress->CheckedChanged += gcnew System::EventHandler(this, &ClientWindow::rbExpress_CheckedChanged);
			// 
			// rbStandard
			// 
			this->rbStandard->AutoSize = true;
			this->rbStandard->Checked = true;
			this->rbStandard->Location = System::Drawing::Point(23, 35);
			this->rbStandard->Name = L"rbStandard";
			this->rbStandard->Size = System::Drawing::Size(105, 24);
			this->rbStandard->TabIndex = 0;
			this->rbStandard->TabStop = true;
			this->rbStandard->Text = L"Обычная";
			this->rbStandard->UseVisualStyleBackColor = true;
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label30->Location = System::Drawing::Point(18, 16);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(376, 29);
			this->label30->TabIndex = 0;
			this->label30->Text = L"Ориентировочная стоимость";
			// 
			// ClientWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::Color::LightGray;
			this->ClientSize = System::Drawing::Size(1626, 837);
			this->Controls->Add(this->pn_result);
			this->Controls->Add(this->panel1);
			this->Name = L"ClientWindow";
			this->Text = L"Заказ перевозки";
			this->Load += gcnew System::EventHandler(this, &ClientWindow::ClientWindow_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->pn_distant_info->ResumeLayout(false);
			this->pn_distant_info->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->pn_cargo_info->ResumeLayout(false);
			this->pn_cargo_info->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->pn_result->ResumeLayout(false);
			this->pn_result->PerformLayout();
			this->gbDeliveryType->ResumeLayout(false);
			this->gbDeliveryType->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		// ================== ЛОГИКА РАСЧЁТА ==================
	private:
		double ParseDouble(TextBox^ tb)
		{
			if (tb == nullptr || String::IsNullOrWhiteSpace(tb->Text))
				return 0.0;

			String^ text = tb->Text->Trim()->Replace(",", ".");
			double value = 0.0;

			bool ok = Double::TryParse(
				text,
				System::Globalization::NumberStyles::Any,
				System::Globalization::CultureInfo::InvariantCulture,
				value
			);

			return ok ? value : 0.0;
		}

		double GetCargoMultiplier()
		{
			switch (cb_type_cargo->SelectedIndex)
			{
			case 1: return 1.20; // Хрупкое
			case 2: return 0.90; // Документы
			case 3: return 1.50; // Крупногабаритный
			case 4: return 1.70; // Топливо
			case 5: return 2.00; // Газ
			case 6: return 3.00; // Радиоактивные
			default: return 1.00; // Обычный
			}
		}

		double GetDeliveryMultiplier()
		{
			return rbExpress->Checked ? 1.25 : 1.00;
		}

		double GetOptionsCost()
		{
			double sum = 0;

			// Адресные услуги
			if (chb_from_adress->Checked) sum += 710;
			if (chb_where_adress->Checked) sum += 510;

			// Упаковка
			if (checkBox1->Checked) sum += 510; // защитная упаковка
			if (checkBox2->Checked) sum += 600; // палетирование

			// Доставка
			if (checkBox3->Checked) sum += 0;   // доставка на этаж (+0)

			// Документы
			if (checkBox4->Checked) sum += 150;
			if (checkBox5->Checked) sum += 100;

			return sum;
		}

		double GetInsuranceCost()
		{
			// 0.5% от объявленной стоимости
			double declaredCost = ParseDouble(tb_nCost);
			if (declaredCost < 0) declaredCost = 0;
			return declaredCost * 0.005;
		}

		void Recalculate()
		{
			double weight = ParseDouble(tb_weight);
			double volume = ParseDouble(tb_volume);
			double length = ParseDouble(tb_length);

			std::wstring fromCity =
				msclr::interop::marshal_as<std::wstring>(tb_whereFrom->Text);

			std::wstring toCity =
				msclr::interop::marshal_as<std::wstring>(tb_where->Text);

			int distanceKm = ::GetDistanceKm(fromCity, toCity);

			double distanceCost = distanceKm * 12.0; 
			double weightCost = weight * 15.0;
			double volumeCost = volume * 120.0;
			double lengthCost = length * 50.0;

			double baseCost =
				distanceCost +
				weightCost +
				volumeCost +
				lengthCost;

			baseCost *= GetCargoMultiplier();   
			baseCost *= GetDeliveryMultiplier(); 

			double optionsCost = GetOptionsCost();
			double insuranceCost = GetInsuranceCost();

			double total = baseCost + optionsCost + insuranceCost;

			lblDistanceCost->Text =
				L"Расстояние: " + distanceKm + L" км";

			lblWeightCost->Text =
				L"Вес: " + weightCost.ToString("F0") + L" ₽";

			lblOptionsCost->Text =
				L"Доп. услуги: " + optionsCost.ToString("F0") + L" ₽";

			lblInsuranceCost->Text =
				L"Страхование: " + insuranceCost.ToString("F0") + L" ₽";

			lb_COST->Text =
				L"ИТОГО: " + total.ToString("F0") + L" ₽";
		}

		// ================== КОНЕЦ ЛОГИКИ ==================
	private: System::Void AnyValueChanged(System::Object^ sender, System::EventArgs^ e)
	{
		Recalculate();
	}
	private: System::Void ClientWindow_Load(System::Object^ sender, System::EventArgs^ e) {
		Recalculate();
	}
	private: System::Void выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void menuStrip1_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label8_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pn_gruz_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void label7_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void chb_from_adress_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		tb_where_adress->Visible = chb_from_adress->Checked;
	}
	private: System::Void label17_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void chb_where_adress_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		tb_from_adress->Visible = chb_where_adress->Checked;
	}
	private: System::Void tb_from_adress_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label19_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label30_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label35_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lblWeightCost_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lblVolumeCost_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void rbExpress_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btn_on_login_win_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Hide();
		LoginWindow^ loginForm = gcnew LoginWindow();
		loginForm->ShowDialog();
		this->Show();
	}
	};
}
