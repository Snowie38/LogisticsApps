#pragma once

#include "AppStorage.h"
#include "UITheme.h"

namespace LogisticsApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для LoginWindow
	/// </summary>
	public ref class LoginWindow : public System::Windows::Forms::Form
	{
	public:
		LoginWindow(void)
		{
			InitializeComponent();
			AppStorage::Init();
			UITheme::Apply(this);

			_draft = nullptr;
			_senderType = SenderType::Person;
			_recipientType = 0;
		}

		LoginWindow(OrderDraft^ draft)
		{
			InitializeComponent();
			AppStorage::Init();
			UITheme::Apply(this);

			_draft = draft;
			_senderType = SenderType::Person;
			_recipientType = 0;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~LoginWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Panel^ pnSenderTabs;

	private: System::Windows::Forms::RadioButton^ btnSenderPerson;
	private: System::Windows::Forms::RadioButton^ btnSenderLegal;


	private: System::Windows::Forms::RadioButton^ btnSenderIP;
	private: System::Windows::Forms::Panel^ pnSenderPerson;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker1;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Panel^ pnSenderIP;

	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker2;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::TextBox^ textBox10;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::TextBox^ textBox11;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::TextBox^ textBox12;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::TextBox^ textBox13;
	private: System::Windows::Forms::Panel^ pnSenderLegal;

	private: System::Windows::Forms::Label^ label31;
	private: System::Windows::Forms::TextBox^ textBox24;
	private: System::Windows::Forms::Label^ label30;
	private: System::Windows::Forms::TextBox^ textBox23;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::TextBox^ textBox15;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::TextBox^ textBox16;
	private: System::Windows::Forms::Label^ label22;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker3;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::TextBox^ textBox17;
	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::TextBox^ textBox18;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::TextBox^ textBox19;
	private: System::Windows::Forms::Label^ label27;
	private: System::Windows::Forms::TextBox^ textBox20;
	private: System::Windows::Forms::Label^ label28;
	private: System::Windows::Forms::TextBox^ textBox21;
	private: System::Windows::Forms::Label^ label29;
	private: System::Windows::Forms::TextBox^ textBox22;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::TextBox^ textBox14;
	private: System::Windows::Forms::Panel^ pnRecipientLegal;



	private: System::Windows::Forms::Label^ label32;
	private: System::Windows::Forms::TextBox^ textBox25;
	private: System::Windows::Forms::Label^ label33;
	private: System::Windows::Forms::TextBox^ textBox26;
	private: System::Windows::Forms::Label^ label34;
	private: System::Windows::Forms::TextBox^ textBox27;
	private: System::Windows::Forms::Label^ label35;
	private: System::Windows::Forms::TextBox^ textBox28;
	private: System::Windows::Forms::Label^ label36;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker4;
	private: System::Windows::Forms::Label^ label37;
	private: System::Windows::Forms::Label^ label38;
	private: System::Windows::Forms::TextBox^ textBox29;
	private: System::Windows::Forms::Label^ label39;
	private: System::Windows::Forms::TextBox^ textBox30;
	private: System::Windows::Forms::Label^ label40;
	private: System::Windows::Forms::TextBox^ textBox31;
	private: System::Windows::Forms::Label^ label41;
	private: System::Windows::Forms::TextBox^ textBox32;
	private: System::Windows::Forms::Label^ label42;
	private: System::Windows::Forms::TextBox^ textBox33;
	private: System::Windows::Forms::Label^ label43;
	private: System::Windows::Forms::TextBox^ textBox34;
	private: System::Windows::Forms::Panel^ pnRecipientIP;


	private: System::Windows::Forms::Label^ label44;
	private: System::Windows::Forms::TextBox^ textBox35;
	private: System::Windows::Forms::Label^ label45;
	private: System::Windows::Forms::TextBox^ textBox36;
	private: System::Windows::Forms::Label^ label46;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker5;
	private: System::Windows::Forms::Label^ label47;
	private: System::Windows::Forms::Label^ label48;
	private: System::Windows::Forms::TextBox^ textBox37;
	private: System::Windows::Forms::Label^ label49;
	private: System::Windows::Forms::TextBox^ textBox38;
	private: System::Windows::Forms::Label^ label50;
	private: System::Windows::Forms::TextBox^ textBox39;
	private: System::Windows::Forms::Label^ label51;
	private: System::Windows::Forms::TextBox^ textBox40;
	private: System::Windows::Forms::Label^ label52;
	private: System::Windows::Forms::TextBox^ textBox41;
	private: System::Windows::Forms::Label^ label53;
	private: System::Windows::Forms::TextBox^ textBox42;
	private: System::Windows::Forms::Panel^ pnRecipientPerson;


	private: System::Windows::Forms::Label^ label54;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker6;
	private: System::Windows::Forms::Label^ label55;
	private: System::Windows::Forms::Label^ label56;
	private: System::Windows::Forms::TextBox^ textBox43;
	private: System::Windows::Forms::Label^ label57;
	private: System::Windows::Forms::TextBox^ textBox44;
	private: System::Windows::Forms::Label^ label58;
	private: System::Windows::Forms::TextBox^ textBox45;
	private: System::Windows::Forms::Label^ label59;
	private: System::Windows::Forms::TextBox^ textBox46;
	private: System::Windows::Forms::Label^ label60;
	private: System::Windows::Forms::TextBox^ textBox47;
	private: System::Windows::Forms::Label^ label61;
	private: System::Windows::Forms::TextBox^ textBox48;
	private: System::Windows::Forms::Panel^ panel5;
	private: System::Windows::Forms::RadioButton^ btnRecipientLegacy;

	private: System::Windows::Forms::RadioButton^ btnRecipientIP;



	private: System::Windows::Forms::RadioButton^ btnRecipientPerson;


	private: System::Windows::Forms::Label^ label62;
	private: System::Windows::Forms::Button^ btnApproveForms;


	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->pnRecipientIP = (gcnew System::Windows::Forms::Panel());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->textBox35 = (gcnew System::Windows::Forms::TextBox());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->textBox36 = (gcnew System::Windows::Forms::TextBox());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker5 = (gcnew System::Windows::Forms::DateTimePicker());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->textBox37 = (gcnew System::Windows::Forms::TextBox());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->textBox38 = (gcnew System::Windows::Forms::TextBox());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->textBox39 = (gcnew System::Windows::Forms::TextBox());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->textBox40 = (gcnew System::Windows::Forms::TextBox());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->textBox41 = (gcnew System::Windows::Forms::TextBox());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->textBox42 = (gcnew System::Windows::Forms::TextBox());
			this->pnRecipientPerson = (gcnew System::Windows::Forms::Panel());
			this->pnRecipientLegal = (gcnew System::Windows::Forms::Panel());
			this->textBox25 = (gcnew System::Windows::Forms::TextBox());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->textBox26 = (gcnew System::Windows::Forms::TextBox());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->textBox27 = (gcnew System::Windows::Forms::TextBox());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->textBox28 = (gcnew System::Windows::Forms::TextBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker4 = (gcnew System::Windows::Forms::DateTimePicker());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->textBox29 = (gcnew System::Windows::Forms::TextBox());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->textBox30 = (gcnew System::Windows::Forms::TextBox());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->textBox31 = (gcnew System::Windows::Forms::TextBox());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->textBox32 = (gcnew System::Windows::Forms::TextBox());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->textBox33 = (gcnew System::Windows::Forms::TextBox());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->textBox34 = (gcnew System::Windows::Forms::TextBox());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker6 = (gcnew System::Windows::Forms::DateTimePicker());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->textBox43 = (gcnew System::Windows::Forms::TextBox());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->textBox44 = (gcnew System::Windows::Forms::TextBox());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->textBox45 = (gcnew System::Windows::Forms::TextBox());
			this->label59 = (gcnew System::Windows::Forms::Label());
			this->textBox46 = (gcnew System::Windows::Forms::TextBox());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->textBox47 = (gcnew System::Windows::Forms::TextBox());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->textBox48 = (gcnew System::Windows::Forms::TextBox());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->btnRecipientLegacy = (gcnew System::Windows::Forms::RadioButton());
			this->btnRecipientIP = (gcnew System::Windows::Forms::RadioButton());
			this->btnRecipientPerson = (gcnew System::Windows::Forms::RadioButton());
			this->label62 = (gcnew System::Windows::Forms::Label());
			this->pnSenderLegal = (gcnew System::Windows::Forms::Panel());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->textBox24 = (gcnew System::Windows::Forms::TextBox());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->textBox23 = (gcnew System::Windows::Forms::TextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker3 = (gcnew System::Windows::Forms::DateTimePicker());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->textBox19 = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->textBox20 = (gcnew System::Windows::Forms::TextBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->textBox21 = (gcnew System::Windows::Forms::TextBox());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->textBox22 = (gcnew System::Windows::Forms::TextBox());
			this->pnSenderIP = (gcnew System::Windows::Forms::Panel());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker2 = (gcnew System::Windows::Forms::DateTimePicker());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->pnSenderPerson = (gcnew System::Windows::Forms::Panel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->pnSenderTabs = (gcnew System::Windows::Forms::Panel());
			this->btnSenderLegal = (gcnew System::Windows::Forms::RadioButton());
			this->btnSenderIP = (gcnew System::Windows::Forms::RadioButton());
			this->btnSenderPerson = (gcnew System::Windows::Forms::RadioButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnApproveForms = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->pnRecipientIP->SuspendLayout();
			this->pnRecipientPerson->SuspendLayout();
			this->pnRecipientLegal->SuspendLayout();
			this->panel5->SuspendLayout();
			this->pnSenderLegal->SuspendLayout();
			this->pnSenderIP->SuspendLayout();
			this->pnSenderPerson->SuspendLayout();
			this->pnSenderTabs->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::WhiteSmoke;
			this->panel1->Controls->Add(this->btnApproveForms);
			this->panel1->Controls->Add(this->pnRecipientIP);
			this->panel1->Controls->Add(this->pnRecipientLegal);
			this->panel1->Controls->Add(this->panel5);
			this->panel1->Controls->Add(this->label62);
			this->panel1->Controls->Add(this->pnSenderLegal);
			this->panel1->Controls->Add(this->pnSenderIP);
			this->panel1->Controls->Add(this->pnSenderPerson);
			this->panel1->Controls->Add(this->pnSenderTabs);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->pnRecipientPerson);
			this->panel1->Location = System::Drawing::Point(402, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(872, 1240);
			this->panel1->TabIndex = 0;
			// 
			// pnRecipientIP
			// 
			this->pnRecipientIP->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnRecipientIP->Controls->Add(this->label44);
			this->pnRecipientIP->Controls->Add(this->textBox35);
			this->pnRecipientIP->Controls->Add(this->label45);
			this->pnRecipientIP->Controls->Add(this->textBox36);
			this->pnRecipientIP->Controls->Add(this->label46);
			this->pnRecipientIP->Controls->Add(this->dateTimePicker5);
			this->pnRecipientIP->Controls->Add(this->label47);
			this->pnRecipientIP->Controls->Add(this->label48);
			this->pnRecipientIP->Controls->Add(this->textBox37);
			this->pnRecipientIP->Controls->Add(this->label49);
			this->pnRecipientIP->Controls->Add(this->textBox38);
			this->pnRecipientIP->Controls->Add(this->label50);
			this->pnRecipientIP->Controls->Add(this->textBox39);
			this->pnRecipientIP->Controls->Add(this->label51);
			this->pnRecipientIP->Controls->Add(this->textBox40);
			this->pnRecipientIP->Controls->Add(this->label52);
			this->pnRecipientIP->Controls->Add(this->textBox41);
			this->pnRecipientIP->Controls->Add(this->label53);
			this->pnRecipientIP->Controls->Add(this->textBox42);
			this->pnRecipientIP->Location = System::Drawing::Point(18, 704);
			this->pnRecipientIP->Name = L"pnRecipientIP";
			this->pnRecipientIP->Size = System::Drawing::Size(844, 345);
			this->pnRecipientIP->TabIndex = 1005;
			// 
			// label44
			// 
			this->label44->AutoSize = true;
			this->label44->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label44->Location = System::Drawing::Point(213, 16);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(134, 20);
			this->label44->TabIndex = 1000;
			this->label44->Text = L"Наименование";
			// 
			// textBox35
			// 
			this->textBox35->Location = System::Drawing::Point(217, 47);
			this->textBox35->MaxLength = 100;
			this->textBox35->Multiline = true;
			this->textBox35->Name = L"textBox35";
			this->textBox35->Size = System::Drawing::Size(139, 41);
			this->textBox35->TabIndex = 19;
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label45->Location = System::Drawing::Point(18, 16);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(75, 20);
			this->label45->TabIndex = 18;
			this->label45->Text = L"ИНН ИП";
			// 
			// textBox36
			// 
			this->textBox36->Location = System::Drawing::Point(22, 47);
			this->textBox36->MaxLength = 100;
			this->textBox36->Name = L"textBox36";
			this->textBox36->Size = System::Drawing::Size(139, 22);
			this->textBox36->TabIndex = 17;
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label46->Location = System::Drawing::Point(397, 267);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(121, 20);
			this->label46->TabIndex = 16;
			this->label46->Text = L"Дата выдачи";
			// 
			// dateTimePicker5
			// 
			this->dateTimePicker5->Location = System::Drawing::Point(394, 290);
			this->dateTimePicker5->Name = L"dateTimePicker5";
			this->dateTimePicker5->Size = System::Drawing::Size(146, 22);
			this->dateTimePicker5->TabIndex = 15;
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label47->Location = System::Drawing::Point(18, 244);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(86, 20);
			this->label47->TabIndex = 14;
			this->label47->Text = L"Паспорт:";
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label48->Location = System::Drawing::Point(192, 269);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(64, 20);
			this->label48->TabIndex = 13;
			this->label48->Text = L"Номер";
			// 
			// textBox37
			// 
			this->textBox37->Location = System::Drawing::Point(196, 292);
			this->textBox37->MaxLength = 4;
			this->textBox37->Name = L"textBox37";
			this->textBox37->Size = System::Drawing::Size(139, 22);
			this->textBox37->TabIndex = 12;
			// 
			// label49
			// 
			this->label49->AutoSize = true;
			this->label49->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label49->Location = System::Drawing::Point(18, 269);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(61, 20);
			this->label49->TabIndex = 11;
			this->label49->Text = L"Серия";
			// 
			// textBox38
			// 
			this->textBox38->Location = System::Drawing::Point(22, 292);
			this->textBox38->MaxLength = 4;
			this->textBox38->Name = L"textBox38";
			this->textBox38->Size = System::Drawing::Size(139, 22);
			this->textBox38->TabIndex = 10;
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label50->Location = System::Drawing::Point(397, 165);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(91, 20);
			this->label50->TabIndex = 9;
			this->label50->Text = L"Отчество";
			// 
			// textBox39
			// 
			this->textBox39->Location = System::Drawing::Point(401, 188);
			this->textBox39->MaxLength = 100;
			this->textBox39->Name = L"textBox39";
			this->textBox39->Size = System::Drawing::Size(139, 22);
			this->textBox39->TabIndex = 8;
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label51->Location = System::Drawing::Point(222, 165);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(42, 20);
			this->label51->TabIndex = 7;
			this->label51->Text = L"Имя";
			// 
			// textBox40
			// 
			this->textBox40->Location = System::Drawing::Point(226, 188);
			this->textBox40->MaxLength = 100;
			this->textBox40->Name = L"textBox40";
			this->textBox40->Size = System::Drawing::Size(139, 22);
			this->textBox40->TabIndex = 6;
			// 
			// label52
			// 
			this->label52->AutoSize = true;
			this->label52->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label52->Location = System::Drawing::Point(18, 165);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(87, 20);
			this->label52->TabIndex = 5;
			this->label52->Text = L"Фамилия";
			// 
			// textBox41
			// 
			this->textBox41->Location = System::Drawing::Point(22, 188);
			this->textBox41->MaxLength = 100;
			this->textBox41->Name = L"textBox41";
			this->textBox41->Size = System::Drawing::Size(139, 22);
			this->textBox41->TabIndex = 4;
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label53->Location = System::Drawing::Point(18, 116);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(90, 20);
			this->label53->TabIndex = 3;
			this->label53->Text = L"Телефон:";
			// 
			// textBox42
			// 
			this->textBox42->Location = System::Drawing::Point(127, 116);
			this->textBox42->MaxLength = 12;
			this->textBox42->Name = L"textBox42";
			this->textBox42->Size = System::Drawing::Size(210, 22);
			this->textBox42->TabIndex = 2;
			// 
			// pnRecipientPerson
			// 
			this->pnRecipientPerson->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnRecipientPerson->Controls->Add(this->label54);
			this->pnRecipientPerson->Controls->Add(this->dateTimePicker6);
			this->pnRecipientPerson->Controls->Add(this->label55);
			this->pnRecipientPerson->Controls->Add(this->label56);
			this->pnRecipientPerson->Controls->Add(this->textBox43);
			this->pnRecipientPerson->Controls->Add(this->label57);
			this->pnRecipientPerson->Controls->Add(this->textBox44);
			this->pnRecipientPerson->Controls->Add(this->label58);
			this->pnRecipientPerson->Controls->Add(this->textBox45);
			this->pnRecipientPerson->Controls->Add(this->label59);
			this->pnRecipientPerson->Controls->Add(this->textBox46);
			this->pnRecipientPerson->Controls->Add(this->label60);
			this->pnRecipientPerson->Controls->Add(this->textBox47);
			this->pnRecipientPerson->Controls->Add(this->label61);
			this->pnRecipientPerson->Controls->Add(this->textBox48);
			this->pnRecipientPerson->Location = System::Drawing::Point(18, 708);
			this->pnRecipientPerson->Name = L"pnRecipientPerson";
			this->pnRecipientPerson->Size = System::Drawing::Size(844, 236);
			this->pnRecipientPerson->TabIndex = 1003;
			// 
			// pnRecipientLegal
			// 
			this->pnRecipientLegal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnRecipientLegal->Controls->Add(this->textBox25);
			this->pnRecipientLegal->Controls->Add(this->label33);
			this->pnRecipientLegal->Controls->Add(this->textBox26);
			this->pnRecipientLegal->Controls->Add(this->label34);
			this->pnRecipientLegal->Controls->Add(this->textBox27);
			this->pnRecipientLegal->Controls->Add(this->label35);
			this->pnRecipientLegal->Controls->Add(this->textBox28);
			this->pnRecipientLegal->Controls->Add(this->label36);
			this->pnRecipientLegal->Controls->Add(this->dateTimePicker4);
			this->pnRecipientLegal->Controls->Add(this->label37);
			this->pnRecipientLegal->Controls->Add(this->label38);
			this->pnRecipientLegal->Controls->Add(this->textBox29);
			this->pnRecipientLegal->Controls->Add(this->label39);
			this->pnRecipientLegal->Controls->Add(this->textBox30);
			this->pnRecipientLegal->Controls->Add(this->label40);
			this->pnRecipientLegal->Controls->Add(this->textBox31);
			this->pnRecipientLegal->Controls->Add(this->label41);
			this->pnRecipientLegal->Controls->Add(this->textBox32);
			this->pnRecipientLegal->Controls->Add(this->label42);
			this->pnRecipientLegal->Controls->Add(this->textBox33);
			this->pnRecipientLegal->Controls->Add(this->label43);
			this->pnRecipientLegal->Controls->Add(this->textBox34);
			this->pnRecipientLegal->Controls->Add(this->label32);
			this->pnRecipientLegal->Location = System::Drawing::Point(18, 708);
			this->pnRecipientLegal->Name = L"pnRecipientLegal";
			this->pnRecipientLegal->Size = System::Drawing::Size(844, 345);
			this->pnRecipientLegal->TabIndex = 1006;
			// 
			// textBox25
			// 
			this->textBox25->Location = System::Drawing::Point(492, 43);
			this->textBox25->MaxLength = 10;
			this->textBox25->Name = L"textBox25";
			this->textBox25->Size = System::Drawing::Size(82, 22);
			this->textBox25->TabIndex = 1003;
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label33->Location = System::Drawing::Point(387, 16);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(51, 20);
			this->label33->TabIndex = 1002;
			this->label33->Text = L"ОПФ";
			// 
			// textBox26
			// 
			this->textBox26->Location = System::Drawing::Point(391, 43);
			this->textBox26->MaxLength = 3;
			this->textBox26->Name = L"textBox26";
			this->textBox26->Size = System::Drawing::Size(60, 22);
			this->textBox26->TabIndex = 1001;
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label34->Location = System::Drawing::Point(213, 16);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(134, 20);
			this->label34->TabIndex = 1000;
			this->label34->Text = L"Наименование";
			// 
			// textBox27
			// 
			this->textBox27->Location = System::Drawing::Point(217, 47);
			this->textBox27->MaxLength = 100;
			this->textBox27->Multiline = true;
			this->textBox27->Name = L"textBox27";
			this->textBox27->Size = System::Drawing::Size(139, 41);
			this->textBox27->TabIndex = 19;
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label35->Location = System::Drawing::Point(18, 16);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(127, 20);
			this->label35->TabIndex = 18;
			this->label35->Text = L"ИНН Юр. Лица";
			// 
			// textBox28
			// 
			this->textBox28->Location = System::Drawing::Point(22, 47);
			this->textBox28->MaxLength = 100;
			this->textBox28->Name = L"textBox28";
			this->textBox28->Size = System::Drawing::Size(139, 22);
			this->textBox28->TabIndex = 17;
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label36->Location = System::Drawing::Point(397, 267);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(121, 20);
			this->label36->TabIndex = 16;
			this->label36->Text = L"Дата выдачи";
			// 
			// dateTimePicker4
			// 
			this->dateTimePicker4->Location = System::Drawing::Point(394, 290);
			this->dateTimePicker4->Name = L"dateTimePicker4";
			this->dateTimePicker4->Size = System::Drawing::Size(146, 22);
			this->dateTimePicker4->TabIndex = 15;
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label37->Location = System::Drawing::Point(18, 244);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(86, 20);
			this->label37->TabIndex = 14;
			this->label37->Text = L"Паспорт:";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label38->Location = System::Drawing::Point(192, 269);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(64, 20);
			this->label38->TabIndex = 13;
			this->label38->Text = L"Номер";
			// 
			// textBox29
			// 
			this->textBox29->Location = System::Drawing::Point(196, 292);
			this->textBox29->MaxLength = 4;
			this->textBox29->Name = L"textBox29";
			this->textBox29->Size = System::Drawing::Size(139, 22);
			this->textBox29->TabIndex = 12;
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label39->Location = System::Drawing::Point(18, 269);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(61, 20);
			this->label39->TabIndex = 11;
			this->label39->Text = L"Серия";
			// 
			// textBox30
			// 
			this->textBox30->Location = System::Drawing::Point(22, 292);
			this->textBox30->MaxLength = 4;
			this->textBox30->Name = L"textBox30";
			this->textBox30->Size = System::Drawing::Size(139, 22);
			this->textBox30->TabIndex = 10;
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label40->Location = System::Drawing::Point(397, 165);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(91, 20);
			this->label40->TabIndex = 9;
			this->label40->Text = L"Отчество";
			// 
			// textBox31
			// 
			this->textBox31->Location = System::Drawing::Point(401, 188);
			this->textBox31->MaxLength = 100;
			this->textBox31->Name = L"textBox31";
			this->textBox31->Size = System::Drawing::Size(139, 22);
			this->textBox31->TabIndex = 8;
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label41->Location = System::Drawing::Point(222, 165);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(42, 20);
			this->label41->TabIndex = 7;
			this->label41->Text = L"Имя";
			// 
			// textBox32
			// 
			this->textBox32->Location = System::Drawing::Point(226, 188);
			this->textBox32->MaxLength = 100;
			this->textBox32->Name = L"textBox32";
			this->textBox32->Size = System::Drawing::Size(139, 22);
			this->textBox32->TabIndex = 6;
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label42->Location = System::Drawing::Point(18, 165);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(87, 20);
			this->label42->TabIndex = 5;
			this->label42->Text = L"Фамилия";
			// 
			// textBox33
			// 
			this->textBox33->Location = System::Drawing::Point(22, 188);
			this->textBox33->MaxLength = 100;
			this->textBox33->Name = L"textBox33";
			this->textBox33->Size = System::Drawing::Size(139, 22);
			this->textBox33->TabIndex = 4;
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label43->Location = System::Drawing::Point(18, 116);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(90, 20);
			this->label43->TabIndex = 3;
			this->label43->Text = L"Телефон:";
			// 
			// textBox34
			// 
			this->textBox34->Location = System::Drawing::Point(127, 116);
			this->textBox34->MaxLength = 12;
			this->textBox34->Name = L"textBox34";
			this->textBox34->Size = System::Drawing::Size(210, 22);
			this->textBox34->TabIndex = 2;
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label32->Location = System::Drawing::Point(494, 16);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(46, 20);
			this->label32->TabIndex = 1004;
			this->label32->Text = L"КПП";
			// 
			// label54
			// 
			this->label54->AutoSize = true;
			this->label54->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label54->Location = System::Drawing::Point(388, 170);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(121, 20);
			this->label54->TabIndex = 16;
			this->label54->Text = L"Дата выдачи";
			// 
			// dateTimePicker6
			// 
			this->dateTimePicker6->Location = System::Drawing::Point(385, 193);
			this->dateTimePicker6->Name = L"dateTimePicker6";
			this->dateTimePicker6->Size = System::Drawing::Size(146, 22);
			this->dateTimePicker6->TabIndex = 15;
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label55->Location = System::Drawing::Point(9, 147);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(86, 20);
			this->label55->TabIndex = 14;
			this->label55->Text = L"Паспорт:";
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label56->Location = System::Drawing::Point(183, 172);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(64, 20);
			this->label56->TabIndex = 13;
			this->label56->Text = L"Номер";
			// 
			// textBox43
			// 
			this->textBox43->Location = System::Drawing::Point(187, 195);
			this->textBox43->MaxLength = 4;
			this->textBox43->Name = L"textBox43";
			this->textBox43->Size = System::Drawing::Size(139, 22);
			this->textBox43->TabIndex = 12;
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label57->Location = System::Drawing::Point(9, 172);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(61, 20);
			this->label57->TabIndex = 11;
			this->label57->Text = L"Серия";
			// 
			// textBox44
			// 
			this->textBox44->Location = System::Drawing::Point(13, 195);
			this->textBox44->MaxLength = 4;
			this->textBox44->Name = L"textBox44";
			this->textBox44->Size = System::Drawing::Size(139, 22);
			this->textBox44->TabIndex = 10;
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label58->Location = System::Drawing::Point(388, 68);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(91, 20);
			this->label58->TabIndex = 9;
			this->label58->Text = L"Отчество";
			// 
			// textBox45
			// 
			this->textBox45->Location = System::Drawing::Point(392, 91);
			this->textBox45->MaxLength = 100;
			this->textBox45->Name = L"textBox45";
			this->textBox45->Size = System::Drawing::Size(139, 22);
			this->textBox45->TabIndex = 8;
			// 
			// label59
			// 
			this->label59->AutoSize = true;
			this->label59->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label59->Location = System::Drawing::Point(213, 68);
			this->label59->Name = L"label59";
			this->label59->Size = System::Drawing::Size(42, 20);
			this->label59->TabIndex = 7;
			this->label59->Text = L"Имя";
			// 
			// textBox46
			// 
			this->textBox46->Location = System::Drawing::Point(217, 91);
			this->textBox46->MaxLength = 100;
			this->textBox46->Name = L"textBox46";
			this->textBox46->Size = System::Drawing::Size(139, 22);
			this->textBox46->TabIndex = 6;
			// 
			// label60
			// 
			this->label60->AutoSize = true;
			this->label60->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label60->Location = System::Drawing::Point(9, 68);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(87, 20);
			this->label60->TabIndex = 5;
			this->label60->Text = L"Фамилия";
			// 
			// textBox47
			// 
			this->textBox47->Location = System::Drawing::Point(13, 91);
			this->textBox47->MaxLength = 100;
			this->textBox47->Name = L"textBox47";
			this->textBox47->Size = System::Drawing::Size(139, 22);
			this->textBox47->TabIndex = 4;
			// 
			// label61
			// 
			this->label61->AutoSize = true;
			this->label61->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label61->Location = System::Drawing::Point(9, 19);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(90, 20);
			this->label61->TabIndex = 3;
			this->label61->Text = L"Телефон:";
			// 
			// textBox48
			// 
			this->textBox48->Location = System::Drawing::Point(118, 19);
			this->textBox48->MaxLength = 12;
			this->textBox48->Name = L"textBox48";
			this->textBox48->Size = System::Drawing::Size(210, 22);
			this->textBox48->TabIndex = 2;
			// 
			// panel5
			// 
			this->panel5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel5->Controls->Add(this->btnRecipientLegacy);
			this->panel5->Controls->Add(this->btnRecipientIP);
			this->panel5->Controls->Add(this->btnRecipientPerson);
			this->panel5->Location = System::Drawing::Point(18, 576);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(844, 100);
			this->panel5->TabIndex = 1004;
			// 
			// btnRecipientLegacy
			// 
			this->btnRecipientLegacy->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnRecipientLegacy->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnRecipientLegacy->Location = System::Drawing::Point(613, 14);
			this->btnRecipientLegacy->Name = L"btnRecipientLegacy";
			this->btnRecipientLegacy->Size = System::Drawing::Size(199, 71);
			this->btnRecipientLegacy->TabIndex = 2;
			this->btnRecipientLegacy->TabStop = true;
			this->btnRecipientLegacy->Text = L"Юр. Лицо";
			this->btnRecipientLegacy->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRecipientLegacy->UseVisualStyleBackColor = true;
			this->btnRecipientLegacy->CheckedChanged += gcnew System::EventHandler(this, &LoginWindow::btnRecipientLegacy_CheckedChanged);
			// 
			// btnRecipientIP
			// 
			this->btnRecipientIP->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnRecipientIP->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnRecipientIP->Location = System::Drawing::Point(317, 14);
			this->btnRecipientIP->Name = L"btnRecipientIP";
			this->btnRecipientIP->Size = System::Drawing::Size(199, 71);
			this->btnRecipientIP->TabIndex = 1;
			this->btnRecipientIP->TabStop = true;
			this->btnRecipientIP->Text = L"ИП";
			this->btnRecipientIP->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRecipientIP->UseVisualStyleBackColor = true;
			this->btnRecipientIP->CheckedChanged += gcnew System::EventHandler(this, &LoginWindow::btnRecipientIP_CheckedChanged);
			// 
			// btnRecipientPerson
			// 
			this->btnRecipientPerson->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnRecipientPerson->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnRecipientPerson->Location = System::Drawing::Point(13, 14);
			this->btnRecipientPerson->Name = L"btnRecipientPerson";
			this->btnRecipientPerson->Size = System::Drawing::Size(199, 71);
			this->btnRecipientPerson->TabIndex = 0;
			this->btnRecipientPerson->TabStop = true;
			this->btnRecipientPerson->Text = L"Физ. Лицо";
			this->btnRecipientPerson->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRecipientPerson->UseVisualStyleBackColor = true;
			this->btnRecipientPerson->CheckedChanged += gcnew System::EventHandler(this, &LoginWindow::btnRecipientPerson_CheckedChanged);
			// 
			// label62
			// 
			this->label62->AutoSize = true;
			this->label62->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label62->Location = System::Drawing::Point(13, 538);
			this->label62->Name = L"label62";
			this->label62->Size = System::Drawing::Size(130, 25);
			this->label62->TabIndex = 1002;
			this->label62->Text = L"Получатель:";
			// 
			// pnSenderLegal
			// 
			this->pnSenderLegal->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnSenderLegal->Controls->Add(this->label31);
			this->pnSenderLegal->Controls->Add(this->textBox24);
			this->pnSenderLegal->Controls->Add(this->label30);
			this->pnSenderLegal->Controls->Add(this->textBox23);
			this->pnSenderLegal->Controls->Add(this->label20);
			this->pnSenderLegal->Controls->Add(this->textBox15);
			this->pnSenderLegal->Controls->Add(this->label21);
			this->pnSenderLegal->Controls->Add(this->textBox16);
			this->pnSenderLegal->Controls->Add(this->label22);
			this->pnSenderLegal->Controls->Add(this->dateTimePicker3);
			this->pnSenderLegal->Controls->Add(this->label23);
			this->pnSenderLegal->Controls->Add(this->label24);
			this->pnSenderLegal->Controls->Add(this->textBox17);
			this->pnSenderLegal->Controls->Add(this->label25);
			this->pnSenderLegal->Controls->Add(this->textBox18);
			this->pnSenderLegal->Controls->Add(this->label26);
			this->pnSenderLegal->Controls->Add(this->textBox19);
			this->pnSenderLegal->Controls->Add(this->label27);
			this->pnSenderLegal->Controls->Add(this->textBox20);
			this->pnSenderLegal->Controls->Add(this->label28);
			this->pnSenderLegal->Controls->Add(this->textBox21);
			this->pnSenderLegal->Controls->Add(this->label29);
			this->pnSenderLegal->Controls->Add(this->textBox22);
			this->pnSenderLegal->Location = System::Drawing::Point(18, 188);
			this->pnSenderLegal->Name = L"pnSenderLegal";
			this->pnSenderLegal->Size = System::Drawing::Size(844, 338);
			this->pnSenderLegal->TabIndex = 1001;
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label31->Location = System::Drawing::Point(488, 16);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(46, 20);
			this->label31->TabIndex = 1004;
			this->label31->Text = L"КПП";
			// 
			// textBox24
			// 
			this->textBox24->Location = System::Drawing::Point(492, 43);
			this->textBox24->MaxLength = 10;
			this->textBox24->Name = L"textBox24";
			this->textBox24->Size = System::Drawing::Size(82, 22);
			this->textBox24->TabIndex = 1003;
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label30->Location = System::Drawing::Point(387, 16);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(51, 20);
			this->label30->TabIndex = 1002;
			this->label30->Text = L"ОПФ";
			// 
			// textBox23
			// 
			this->textBox23->Location = System::Drawing::Point(391, 43);
			this->textBox23->MaxLength = 3;
			this->textBox23->Name = L"textBox23";
			this->textBox23->Size = System::Drawing::Size(60, 22);
			this->textBox23->TabIndex = 1001;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label20->Location = System::Drawing::Point(213, 16);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(134, 20);
			this->label20->TabIndex = 1000;
			this->label20->Text = L"Наименование";
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(217, 47);
			this->textBox15->MaxLength = 100;
			this->textBox15->Multiline = true;
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(139, 41);
			this->textBox15->TabIndex = 19;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label21->Location = System::Drawing::Point(18, 16);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(127, 20);
			this->label21->TabIndex = 18;
			this->label21->Text = L"ИНН Юр. Лица";
			// 
			// textBox16
			// 
			this->textBox16->Location = System::Drawing::Point(22, 47);
			this->textBox16->MaxLength = 100;
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(139, 22);
			this->textBox16->TabIndex = 17;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label22->Location = System::Drawing::Point(397, 267);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(121, 20);
			this->label22->TabIndex = 16;
			this->label22->Text = L"Дата выдачи";
			// 
			// dateTimePicker3
			// 
			this->dateTimePicker3->Location = System::Drawing::Point(394, 290);
			this->dateTimePicker3->Name = L"dateTimePicker3";
			this->dateTimePicker3->Size = System::Drawing::Size(146, 22);
			this->dateTimePicker3->TabIndex = 15;
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label23->Location = System::Drawing::Point(18, 244);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(86, 20);
			this->label23->TabIndex = 14;
			this->label23->Text = L"Паспорт:";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label24->Location = System::Drawing::Point(192, 269);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(64, 20);
			this->label24->TabIndex = 13;
			this->label24->Text = L"Номер";
			// 
			// textBox17
			// 
			this->textBox17->Location = System::Drawing::Point(196, 292);
			this->textBox17->MaxLength = 4;
			this->textBox17->Name = L"textBox17";
			this->textBox17->Size = System::Drawing::Size(139, 22);
			this->textBox17->TabIndex = 12;
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label25->Location = System::Drawing::Point(18, 269);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(61, 20);
			this->label25->TabIndex = 11;
			this->label25->Text = L"Серия";
			// 
			// textBox18
			// 
			this->textBox18->Location = System::Drawing::Point(22, 292);
			this->textBox18->MaxLength = 4;
			this->textBox18->Name = L"textBox18";
			this->textBox18->Size = System::Drawing::Size(139, 22);
			this->textBox18->TabIndex = 10;
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label26->Location = System::Drawing::Point(397, 165);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(91, 20);
			this->label26->TabIndex = 9;
			this->label26->Text = L"Отчество";
			// 
			// textBox19
			// 
			this->textBox19->Location = System::Drawing::Point(401, 188);
			this->textBox19->MaxLength = 100;
			this->textBox19->Name = L"textBox19";
			this->textBox19->Size = System::Drawing::Size(139, 22);
			this->textBox19->TabIndex = 8;
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label27->Location = System::Drawing::Point(222, 165);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(42, 20);
			this->label27->TabIndex = 7;
			this->label27->Text = L"Имя";
			// 
			// textBox20
			// 
			this->textBox20->Location = System::Drawing::Point(226, 188);
			this->textBox20->MaxLength = 100;
			this->textBox20->Name = L"textBox20";
			this->textBox20->Size = System::Drawing::Size(139, 22);
			this->textBox20->TabIndex = 6;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label28->Location = System::Drawing::Point(18, 165);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(87, 20);
			this->label28->TabIndex = 5;
			this->label28->Text = L"Фамилия";
			// 
			// textBox21
			// 
			this->textBox21->Location = System::Drawing::Point(22, 188);
			this->textBox21->MaxLength = 100;
			this->textBox21->Name = L"textBox21";
			this->textBox21->Size = System::Drawing::Size(139, 22);
			this->textBox21->TabIndex = 4;
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label29->Location = System::Drawing::Point(18, 116);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(90, 20);
			this->label29->TabIndex = 3;
			this->label29->Text = L"Телефон:";
			// 
			// textBox22
			// 
			this->textBox22->Location = System::Drawing::Point(127, 116);
			this->textBox22->MaxLength = 12;
			this->textBox22->Name = L"textBox22";
			this->textBox22->Size = System::Drawing::Size(210, 22);
			this->textBox22->TabIndex = 2;
			// 
			// pnSenderIP
			// 
			this->pnSenderIP->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnSenderIP->Controls->Add(this->label19);
			this->pnSenderIP->Controls->Add(this->textBox14);
			this->pnSenderIP->Controls->Add(this->label18);
			this->pnSenderIP->Controls->Add(this->textBox13);
			this->pnSenderIP->Controls->Add(this->label10);
			this->pnSenderIP->Controls->Add(this->dateTimePicker2);
			this->pnSenderIP->Controls->Add(this->label11);
			this->pnSenderIP->Controls->Add(this->label12);
			this->pnSenderIP->Controls->Add(this->textBox7);
			this->pnSenderIP->Controls->Add(this->label13);
			this->pnSenderIP->Controls->Add(this->textBox8);
			this->pnSenderIP->Controls->Add(this->label14);
			this->pnSenderIP->Controls->Add(this->textBox9);
			this->pnSenderIP->Controls->Add(this->label15);
			this->pnSenderIP->Controls->Add(this->textBox10);
			this->pnSenderIP->Controls->Add(this->label16);
			this->pnSenderIP->Controls->Add(this->textBox11);
			this->pnSenderIP->Controls->Add(this->label17);
			this->pnSenderIP->Controls->Add(this->textBox12);
			this->pnSenderIP->Location = System::Drawing::Point(18, 188);
			this->pnSenderIP->Name = L"pnSenderIP";
			this->pnSenderIP->Size = System::Drawing::Size(844, 338);
			this->pnSenderIP->TabIndex = 2;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label19->Location = System::Drawing::Point(213, 16);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(134, 20);
			this->label19->TabIndex = 1000;
			this->label19->Text = L"Наименование";
			// 
			// textBox14
			// 
			this->textBox14->Location = System::Drawing::Point(217, 47);
			this->textBox14->MaxLength = 100;
			this->textBox14->Multiline = true;
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(139, 41);
			this->textBox14->TabIndex = 19;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label18->Location = System::Drawing::Point(18, 16);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(75, 20);
			this->label18->TabIndex = 18;
			this->label18->Text = L"ИНН ИП";
			// 
			// textBox13
			// 
			this->textBox13->Location = System::Drawing::Point(22, 47);
			this->textBox13->MaxLength = 100;
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(139, 22);
			this->textBox13->TabIndex = 17;
			this->textBox13->TextChanged += gcnew System::EventHandler(this, &LoginWindow::textBox13_TextChanged);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(397, 267);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(121, 20);
			this->label10->TabIndex = 16;
			this->label10->Text = L"Дата выдачи";
			// 
			// dateTimePicker2
			// 
			this->dateTimePicker2->Location = System::Drawing::Point(394, 290);
			this->dateTimePicker2->Name = L"dateTimePicker2";
			this->dateTimePicker2->Size = System::Drawing::Size(146, 22);
			this->dateTimePicker2->TabIndex = 15;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(18, 244);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(86, 20);
			this->label11->TabIndex = 14;
			this->label11->Text = L"Паспорт:";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(192, 269);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(64, 20);
			this->label12->TabIndex = 13;
			this->label12->Text = L"Номер";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(196, 292);
			this->textBox7->MaxLength = 4;
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(139, 22);
			this->textBox7->TabIndex = 12;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(18, 269);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(61, 20);
			this->label13->TabIndex = 11;
			this->label13->Text = L"Серия";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(22, 292);
			this->textBox8->MaxLength = 4;
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(139, 22);
			this->textBox8->TabIndex = 10;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(397, 165);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(91, 20);
			this->label14->TabIndex = 9;
			this->label14->Text = L"Отчество";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(401, 188);
			this->textBox9->MaxLength = 100;
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(139, 22);
			this->textBox9->TabIndex = 8;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label15->Location = System::Drawing::Point(222, 165);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(42, 20);
			this->label15->TabIndex = 7;
			this->label15->Text = L"Имя";
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(226, 188);
			this->textBox10->MaxLength = 100;
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(139, 22);
			this->textBox10->TabIndex = 6;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label16->Location = System::Drawing::Point(18, 165);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(87, 20);
			this->label16->TabIndex = 5;
			this->label16->Text = L"Фамилия";
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(22, 188);
			this->textBox11->MaxLength = 100;
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(139, 22);
			this->textBox11->TabIndex = 4;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label17->Location = System::Drawing::Point(18, 116);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(90, 20);
			this->label17->TabIndex = 3;
			this->label17->Text = L"Телефон:";
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(127, 116);
			this->textBox12->MaxLength = 12;
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(210, 22);
			this->textBox12->TabIndex = 2;
			// 
			// pnSenderPerson
			// 
			this->pnSenderPerson->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnSenderPerson->Controls->Add(this->label9);
			this->pnSenderPerson->Controls->Add(this->dateTimePicker1);
			this->pnSenderPerson->Controls->Add(this->label8);
			this->pnSenderPerson->Controls->Add(this->label7);
			this->pnSenderPerson->Controls->Add(this->textBox6);
			this->pnSenderPerson->Controls->Add(this->label6);
			this->pnSenderPerson->Controls->Add(this->textBox5);
			this->pnSenderPerson->Controls->Add(this->label5);
			this->pnSenderPerson->Controls->Add(this->textBox4);
			this->pnSenderPerson->Controls->Add(this->label4);
			this->pnSenderPerson->Controls->Add(this->textBox3);
			this->pnSenderPerson->Controls->Add(this->label3);
			this->pnSenderPerson->Controls->Add(this->textBox2);
			this->pnSenderPerson->Controls->Add(this->label2);
			this->pnSenderPerson->Controls->Add(this->textBox1);
			this->pnSenderPerson->Location = System::Drawing::Point(18, 188);
			this->pnSenderPerson->Name = L"pnSenderPerson";
			this->pnSenderPerson->Size = System::Drawing::Size(844, 236);
			this->pnSenderPerson->TabIndex = 1;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(388, 170);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(121, 20);
			this->label9->TabIndex = 16;
			this->label9->Text = L"Дата выдачи";
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Location = System::Drawing::Point(385, 193);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(146, 22);
			this->dateTimePicker1->TabIndex = 15;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(9, 147);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(86, 20);
			this->label8->TabIndex = 14;
			this->label8->Text = L"Паспорт:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(183, 172);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(64, 20);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Номер";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(187, 195);
			this->textBox6->MaxLength = 4;
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(139, 22);
			this->textBox6->TabIndex = 12;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(9, 172);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(61, 20);
			this->label6->TabIndex = 11;
			this->label6->Text = L"Серия";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(13, 195);
			this->textBox5->MaxLength = 4;
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(139, 22);
			this->textBox5->TabIndex = 10;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(388, 68);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(91, 20);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Отчество";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(392, 91);
			this->textBox4->MaxLength = 100;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(139, 22);
			this->textBox4->TabIndex = 8;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(213, 68);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(42, 20);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Имя";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(217, 91);
			this->textBox3->MaxLength = 100;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(139, 22);
			this->textBox3->TabIndex = 6;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(9, 68);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(87, 20);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Фамилия";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(13, 91);
			this->textBox2->MaxLength = 100;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(139, 22);
			this->textBox2->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(9, 19);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(90, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Телефон:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(118, 19);
			this->textBox1->MaxLength = 12;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(210, 22);
			this->textBox1->TabIndex = 2;
			// 
			// pnSenderTabs
			// 
			this->pnSenderTabs->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnSenderTabs->Controls->Add(this->btnSenderLegal);
			this->pnSenderTabs->Controls->Add(this->btnSenderIP);
			this->pnSenderTabs->Controls->Add(this->btnSenderPerson);
			this->pnSenderTabs->Location = System::Drawing::Point(18, 57);
			this->pnSenderTabs->Name = L"pnSenderTabs";
			this->pnSenderTabs->Size = System::Drawing::Size(844, 100);
			this->pnSenderTabs->TabIndex = 1;
			// 
			// btnSenderLegal
			// 
			this->btnSenderLegal->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnSenderLegal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnSenderLegal->Location = System::Drawing::Point(613, 14);
			this->btnSenderLegal->Name = L"btnSenderLegal";
			this->btnSenderLegal->Size = System::Drawing::Size(199, 71);
			this->btnSenderLegal->TabIndex = 2;
			this->btnSenderLegal->TabStop = true;
			this->btnSenderLegal->Text = L"Юр. Лицо";
			this->btnSenderLegal->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnSenderLegal->UseVisualStyleBackColor = true;
			this->btnSenderLegal->CheckedChanged += gcnew System::EventHandler(this, &LoginWindow::btnSenderLegal_CheckedChanged);
			// 
			// btnSenderIP
			// 
			this->btnSenderIP->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnSenderIP->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnSenderIP->Location = System::Drawing::Point(317, 14);
			this->btnSenderIP->Name = L"btnSenderIP";
			this->btnSenderIP->Size = System::Drawing::Size(199, 71);
			this->btnSenderIP->TabIndex = 1;
			this->btnSenderIP->TabStop = true;
			this->btnSenderIP->Text = L"ИП";
			this->btnSenderIP->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnSenderIP->UseVisualStyleBackColor = true;
			this->btnSenderIP->CheckedChanged += gcnew System::EventHandler(this, &LoginWindow::btnSenderIP_CheckedChanged);
			// 
			// btnSenderPerson
			// 
			this->btnSenderPerson->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnSenderPerson->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnSenderPerson->Location = System::Drawing::Point(13, 14);
			this->btnSenderPerson->Name = L"btnSenderPerson";
			this->btnSenderPerson->Size = System::Drawing::Size(199, 71);
			this->btnSenderPerson->TabIndex = 0;
			this->btnSenderPerson->TabStop = true;
			this->btnSenderPerson->Text = L"Физ. Лицо";
			this->btnSenderPerson->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnSenderPerson->UseVisualStyleBackColor = true;
			this->btnSenderPerson->CheckedChanged += gcnew System::EventHandler(this, &LoginWindow::btnSenderPerson_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(13, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(143, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Отправитель:";
			// 
			// btnApproveForms
			// 
			this->btnApproveForms->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnApproveForms->Location = System::Drawing::Point(201, 1096);
			this->btnApproveForms->Name = L"btnApproveForms";
			this->btnApproveForms->Size = System::Drawing::Size(502, 120);
			this->btnApproveForms->TabIndex = 1007;
			this->btnApproveForms->Text = L"Оформить заявку";
			this->btnApproveForms->UseVisualStyleBackColor = true;
			this->btnApproveForms->Click += gcnew System::EventHandler(this, &LoginWindow::btnApproveForms_Click);
			// 
			// LoginWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::Color::LightGray;
			this->ClientSize = System::Drawing::Size(1605, 820);
			this->Controls->Add(this->panel1);
			this->Name = L"LoginWindow";
			this->Text = L"Заказать перевозку";
			this->Load += gcnew System::EventHandler(this, &LoginWindow::LoginWindow_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->pnRecipientIP->ResumeLayout(false);
			this->pnRecipientIP->PerformLayout();
			this->pnRecipientPerson->ResumeLayout(false);
			this->pnRecipientPerson->PerformLayout();
			this->pnRecipientLegal->ResumeLayout(false);
			this->pnRecipientLegal->PerformLayout();
			this->panel5->ResumeLayout(false);
			this->pnSenderLegal->ResumeLayout(false);
			this->pnSenderLegal->PerformLayout();
			this->pnSenderIP->ResumeLayout(false);
			this->pnSenderIP->PerformLayout();
			this->pnSenderPerson->ResumeLayout(false);
			this->pnSenderPerson->PerformLayout();
			this->pnSenderTabs->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		void SetRecipientType(int type)
		{
			_recipientType = type;
			StyleButton(btnRecipientPerson, type == 0);
			StyleButton(btnRecipientIP, type == 1);
			StyleButton(btnRecipientLegacy, type == 2);
			pnRecipientPerson->Visible = (type == 0);
			pnRecipientIP->Visible = (type == 1);
			pnRecipientLegal->Visible = (type == 2);
		}

	private:
		enum class SenderType { Person, IP, Legal };

		SenderType _senderType;
		int _recipientType;
		OrderDraft^ _draft;

		String^ TrimOrEmpty(String^ s)
		{
			if (String::IsNullOrWhiteSpace(s)) return "";
			return s->Trim();
		}

		String^ CombineFio(String^ fam, String^ name, String^ otch)
		{
			String^ f = TrimOrEmpty(fam);
			String^ n = TrimOrEmpty(name);
			String^ o = TrimOrEmpty(otch);

			System::Collections::Generic::List<String^>^ parts =
				gcnew System::Collections::Generic::List<String^>();

			if (!String::IsNullOrEmpty(f)) parts->Add(f);
			if (!String::IsNullOrEmpty(n)) parts->Add(n);
			if (!String::IsNullOrEmpty(o)) parts->Add(o);

			return String::Join(" ", parts->ToArray());
		}

		void StyleButton(RadioButton^ b, bool isActive)
		{
			System::Drawing::Color active = System::Drawing::Color::FromArgb(55, 77, 143);
			System::Drawing::Color inactive = System::Drawing::Color::White;

			b->BackColor = isActive ? active : inactive;
			b->ForeColor = isActive ? System::Drawing::Color::White : System::Drawing::Color::Black;
			b->FlatStyle = FlatStyle::Flat;
			b->FlatAppearance->BorderColor = System::Drawing::Color::Silver;
		}

		void SetSenderType(SenderType t)
		{
			_senderType = t;
			pnSenderPerson->Visible = (t == SenderType::Person);
			pnSenderIP->Visible = (t == SenderType::IP);
			pnSenderLegal->Visible = (t == SenderType::Legal);

			StyleButton(btnSenderPerson, (t == SenderType::Person));
			StyleButton(btnSenderIP, (t == SenderType::IP));
			StyleButton(btnSenderLegal, (t == SenderType::Legal));
		}

	private: System::Void LoginWindow_Load(System::Object^ sender, System::EventArgs^ e) {
		SetSenderType(SenderType::Person);
		SetRecipientType(0);
	}

	private: System::Void textBox13_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btnSenderPerson_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		SetSenderType(SenderType::Person);
	}
	private: System::Void btnSenderIP_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		SetSenderType(SenderType::IP);
	}
	private: System::Void btnSenderLegal_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		SetSenderType(SenderType::Legal);
	}
	private: System::Void btnRecipientPerson_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		SetRecipientType(0);
	}
	private: System::Void btnRecipientIP_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		SetRecipientType(1);
	}
	private: System::Void btnRecipientLegacy_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		SetRecipientType(2);
	}
	private: System::Void btnApproveForms_Click(System::Object^ sender, System::EventArgs^ e) {
		if (_draft == nullptr)
		{
			MessageBox::Show("Не удалось отправить заказ: отсутствуют данные расчета (вернитесь на окно заказа).", "Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// ---------- Отправитель ----------
		String^ senderTypeStr = "";
		String^ senderName = "";
		String^ senderPhone = "";

		String^ senderInn = "";
		String^ senderOrgName = "";
		String^ senderOpf = "";
		String^ senderKpp = "";
		String^ senderPassSeries = "";
		String^ senderPassNumber = "";
		DateTime senderPassDate = DateTime::MinValue;

		if (_senderType == SenderType::Person)
		{
			senderTypeStr = "Физ. лицо";
			senderPhone = textBox1->Text;
			senderName = CombineFio(textBox2->Text, textBox3->Text, textBox4->Text);

			senderPassSeries = textBox5->Text;
			senderPassNumber = textBox6->Text;
			senderPassDate = dateTimePicker1->Value;
		}
		else if (_senderType == SenderType::IP)
		{
			senderTypeStr = "ИП";
			senderPhone = textBox12->Text;
			senderName = CombineFio(textBox11->Text, textBox10->Text, textBox9->Text);

			senderInn = textBox13->Text;
			senderOrgName = textBox14->Text;

			senderPassSeries = textBox8->Text;
			senderPassNumber = textBox7->Text;
			senderPassDate = dateTimePicker2->Value;
		}
		else // Legal
		{
			senderTypeStr = "Юр. лицо";
			senderPhone = textBox22->Text;
			senderName = CombineFio(textBox21->Text, textBox20->Text, textBox19->Text);

			senderOrgName = textBox15->Text;
			senderInn = textBox16->Text;
			senderOpf = textBox23->Text;
			senderKpp = textBox24->Text;

			senderPassSeries = textBox18->Text;
			senderPassNumber = textBox17->Text;
			senderPassDate = dateTimePicker3->Value;
		}

		// ---------- Получатель ----------
		String^ recipientTypeStr = "";
		String^ recipientName = "";
		String^ recipientPhone = "";

		String^ recipientInn = "";
		String^ recipientOrgName = "";
		String^ recipientOpf = "";
		String^ recipientKpp = "";
		String^ recipientPassSeries = "";
		String^ recipientPassNumber = "";
		DateTime recipientPassDate = DateTime::MinValue;

		if (_recipientType == 0) // Person
		{
			recipientTypeStr = "Физ. лицо";
			recipientPhone = textBox48->Text;
			recipientName = CombineFio(textBox47->Text, textBox46->Text, textBox45->Text);

			recipientPassSeries = textBox44->Text;
			recipientPassNumber = textBox43->Text;
			recipientPassDate = dateTimePicker6->Value;
		}
		else if (_recipientType == 1) // IP
		{
			recipientTypeStr = "ИП";
			recipientPhone = textBox42->Text;
			recipientName = CombineFio(textBox41->Text, textBox40->Text, textBox39->Text);

			recipientInn = textBox36->Text;
			recipientOrgName = textBox35->Text;

			recipientPassSeries = textBox38->Text;
			recipientPassNumber = textBox37->Text;
			recipientPassDate = dateTimePicker5->Value;
		}
		else // Legal
		{
			recipientTypeStr = "Юр. лицо";
			recipientPhone = textBox34->Text;
			recipientName = CombineFio(textBox33->Text, textBox32->Text, textBox31->Text);

			recipientInn = textBox28->Text;
			recipientOrgName = textBox27->Text;
			recipientOpf = textBox26->Text;
			recipientKpp = textBox25->Text;

			recipientPassSeries = textBox30->Text;
			recipientPassNumber = textBox29->Text;
			recipientPassDate = dateTimePicker4->Value;
		}

		// Минимальная валидация
		if (String::IsNullOrWhiteSpace(senderName) || String::IsNullOrWhiteSpace(senderPhone) ||
			String::IsNullOrWhiteSpace(recipientName) || String::IsNullOrWhiteSpace(recipientPhone))
		{
			MessageBox::Show("Заполните ФИО и телефон отправителя/получателя.", "Проверка данных",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		int orderId = AppStorage::AddOrder(
			_draft,
			senderName, senderPhone, senderTypeStr,
			recipientName, recipientPhone, recipientTypeStr,
			senderInn, senderOrgName, senderOpf, senderKpp,
			senderPassSeries, senderPassNumber, senderPassDate,
			recipientInn, recipientOrgName, recipientOpf, recipientKpp,
			recipientPassSeries, recipientPassNumber, recipientPassDate
		);

		if (orderId < 0)
		{
			MessageBox::Show("Не удалось сохранить заказ.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		MessageBox::Show(
			String::Format(
				"Заказ №{0} успешно оформлен.\r\nСумма: {1} руб.\r\nОжидайте звонка оператора.",
				orderId,
				(int)Math::Round(_draft->TotalCost)
			),
			"Успех",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information
		);
		this->Close();
	}
	};
}
