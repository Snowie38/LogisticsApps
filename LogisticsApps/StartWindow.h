#pragma once

#include "ClientWindow.h"
#include "AdminWindow.h"
#include "UITheme.h"

namespace LogisticsApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class StartWindow : public System::Windows::Forms::Form
	{
	public:
		StartWindow(void)
		{
			InitializeComponent();
			UITheme::Apply(this);
			UITheme::StyleCard(panel1);
			UITheme::StyleLabel(label1, true);
			UITheme::StyleLabel(label2, false);

		}

	protected:
		~StartWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ btn_Admin_Start;
	private: System::Windows::Forms::Button^ btn_Client_Start;
	private: System::Windows::Forms::Label^ label2;
	protected:
	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->btn_Admin_Start = (gcnew System::Windows::Forms::Button());
			this->btn_Client_Start = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::Menu;
			this->panel1->Controls->Add(this->btn_Admin_Start);
			this->panel1->Controls->Add(this->btn_Client_Start);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Location = System::Drawing::Point(504, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(550, 796);
			this->panel1->TabIndex = 0;
			// 
			// btn_Admin_Start
			// 
			this->btn_Admin_Start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btn_Admin_Start->Location = System::Drawing::Point(98, 584);
			this->btn_Admin_Start->Name = L"btn_Admin_Start";
			this->btn_Admin_Start->Size = System::Drawing::Size(392, 186);
			this->btn_Admin_Start->TabIndex = 3;
			this->btn_Admin_Start->Text = L"Администрирование";
			this->btn_Admin_Start->UseVisualStyleBackColor = true;
			this->btn_Admin_Start->Click += gcnew System::EventHandler(this, &StartWindow::btn_Admin_Click);
			// 
			// btn_Client_Start
			// 
			this->btn_Client_Start->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->btn_Client_Start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btn_Client_Start->Location = System::Drawing::Point(98, 354);
			this->btn_Client_Start->Name = L"btn_Client_Start";
			this->btn_Client_Start->Size = System::Drawing::Size(393, 185);
			this->btn_Client_Start->TabIndex = 2;
			this->btn_Client_Start->Text = L"Заказать перевозку";
			this->btn_Client_Start->UseVisualStyleBackColor = true;
			this->btn_Client_Start->Click += gcnew System::EventHandler(this, &StartWindow::btn_Client_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(190, 124);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(328, 25);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Выберите нужный пункт меню";
			this->label2->Click += gcnew System::EventHandler(this, &StartWindow::label2_Click);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft JhengHei", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(44, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(591, 53);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Автомобильные перевозки";
			this->label1->Click += gcnew System::EventHandler(this, &StartWindow::label1_Click);
			// 
			// StartWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(1500, 820);
			this->Controls->Add(this->panel1);
			this->Name = L"StartWindow";
			this->Text = L"Автомобильные перевозки";
			this->Load += gcnew System::EventHandler(this, &StartWindow::StartWindow_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void StartWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btn_Client_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Hide();
		ClientWindow^ client = gcnew ClientWindow();
		client->ShowDialog();
		this->Show();
	}
	private: System::Void btn_Admin_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Hide();
		AdminWindow^ admin = gcnew AdminWindow();
		admin->ShowDialog();
		this->Show();
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
