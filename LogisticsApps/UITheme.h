#pragma once

// UITheme.h
// Единый набор цветов/шрифтов/стилей для WinForms (под дизайн из AdminWindow)
// Логику и обработчики не затрагивает — только визуал.

namespace LogisticsApp {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;

	public ref class UITheme abstract sealed
	{
	public:
		// ---- Палитра (соответствует AdminWindow) ----
		literal int kSidebarW = 260;

		static Color AppBg()			{ return Color::FromArgb(240, 242, 245); }
		static Color CardBg()		{ return Color::White; }
		static Color Border()		{ return Color::FromArgb(220, 224, 230); }

		static Color Dark()			{ return Color::FromArgb(32, 36, 48); }
		static Color DarkHover()	{ return Color::FromArgb(52, 58, 76); }
		static Color Text()			{ return Color::FromArgb(40, 40, 40); }
		static Color MutedText()	{ return Color::FromArgb(110, 110, 110); }

		// ---- Шрифты ----
		static Drawing::Font^ H1()	{ return gcnew Drawing::Font(L"Segoe UI", 16, FontStyle::Bold); }
		static Drawing::Font^ H2()	{ return gcnew Drawing::Font(L"Segoe UI", 12, FontStyle::Bold); }
		static Drawing::Font^ Body(){ return gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Regular); }

		// Главная точка: применить тему к окну и всем дочерним контролам.
		static void Apply(Form^ form)
		{
			if (form == nullptr) return;
			form->Font = Body();
			form->BackColor = AppBg();
			form->AutoScaleMode = AutoScaleMode::Font;
			ApplyControlTree(form);
		}

		// Стиль "карточки" (белая панель с рамкой)
		static void StyleCard(Panel^ p)
		{
			if (p == nullptr) return;
			p->BackColor = CardBg();
			p->BorderStyle = BorderStyle::FixedSingle;
		}

		// Основная кнопка
		static void StylePrimaryButton(Button^ b)
		{
			if (b == nullptr) return;
			b->FlatStyle = FlatStyle::Flat;
			b->FlatAppearance->BorderSize = 0;
			b->BackColor = Dark();
			b->ForeColor = Color::White;
			b->Font = gcnew Drawing::Font(L"Segoe UI", 11, FontStyle::Bold);
			b->Cursor = Cursors::Hand;
			b->UseVisualStyleBackColor = false;

			// Ховер — только для нормального состояния
			b->MouseEnter += gcnew EventHandler(&UITheme::OnPrimaryEnter);
			b->MouseLeave += gcnew EventHandler(&UITheme::OnPrimaryLeave);
		}

		// Вторичная (светлая) кнопка
		static void StyleSecondaryButton(Button^ b)
		{
			if (b == nullptr) return;
			b->FlatStyle = FlatStyle::Flat;
			b->FlatAppearance->BorderSize = 1;
			b->FlatAppearance->BorderColor = Border();
			b->BackColor = CardBg();
			b->ForeColor = Text();
			b->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Regular);
			b->Cursor = Cursors::Hand;
			b->UseVisualStyleBackColor = false;
		}

		static void StyleTextBox(TextBox^ t)
		{
			if (t == nullptr) return;
			t->Font = Body();
			t->BorderStyle = BorderStyle::FixedSingle;
			t->BackColor = Color::White;
			// ForeColor оставляем по умолчанию — в некоторых местах используется для валидации/подсветки
		}

		static void StyleLabel(Label^ l, bool isTitle)
		{
			if (l == nullptr) return;
			l->Font = isTitle ? H1() : Body();
			l->ForeColor = isTitle ? Text() : MutedText();
		}

		static void StyleGrid(DataGridView^ g)
		{
			if (g == nullptr) return;
			g->BorderStyle = BorderStyle::None;
			g->BackgroundColor = CardBg();
			g->EnableHeadersVisualStyles = false;
			g->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
			g->RowHeadersVisible = false;
			g->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			g->MultiSelect = false;
			g->Font = Body();

			g->ColumnHeadersDefaultCellStyle->BackColor = Dark();
			g->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
			g->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
			g->ColumnHeadersDefaultCellStyle->Padding = Padding(8, 6, 8, 6);

			g->DefaultCellStyle->BackColor = CardBg();
			g->DefaultCellStyle->ForeColor = Text();
			g->DefaultCellStyle->SelectionBackColor = Color::FromArgb(230, 233, 239);
			g->DefaultCellStyle->SelectionForeColor = Text();
			g->DefaultCellStyle->Padding = Padding(8, 4, 8, 4);
		}

	private:
		static void ApplyControlTree(Control^ root)
		{
			if (root == nullptr) return;

			// Не ломаем AdminWindow (он собирает UI программно)
			// И вообще не трогаем темные навигационные кнопки — они там стилизованы вручную.
			for each (Control ^ c in root->Controls)
			{
				// Фоны панелей: серый внешний, белый — как карточка.
				if (dynamic_cast<Panel^>(c) != nullptr)
				{
					Panel^ p = (Panel^)c;
					// Если панель в дизайнере была SystemColors::Menu / ControlLightLight — считаем ее карточкой
					if (p->BackColor == SystemColors::Menu || p->BackColor == SystemColors::ControlLightLight || p->BackColor == SystemColors::Window)
					{
						StyleCard(p);
					}
					else
					{
						// Остальным панелям отдаем общий фон
						p->BackColor = AppBg();
					}
				}

				if (dynamic_cast<Label^>(c) != nullptr)
				{
					Label^ l = (Label^)c;
					// Крупные заголовки (если вдруг они были более 14pt)
					bool isTitle = (l->Font != nullptr && l->Font->Size >= 14.0f);
					StyleLabel(l, isTitle);
				}

				if (dynamic_cast<TextBox^>(c) != nullptr)
					StyleTextBox((TextBox^)c);

				if (dynamic_cast<DataGridView^>(c) != nullptr)
					StyleGrid((DataGridView^)c);

				if (dynamic_cast<Button^>(c) != nullptr)
				{
					Button^ b = (Button^)c;
					// Не трогаем навигацию в AdminWindow: она имеет фон Dark и ForeColor ~220
					bool looksLikeNav = (b->BackColor == Dark() && b->ForeColor.R > 180 && b->ForeColor.G > 180);
					if (!looksLikeNav)
						StylePrimaryButton(b);
				}

				// Рекурсия
				if (c->HasChildren)
					ApplyControlTree(c);
			}
		}

		static void OnPrimaryEnter(Object^ sender, EventArgs^)
		{
			Button^ b = dynamic_cast<Button^>(sender);
			if (b != nullptr) b->BackColor = DarkHover();
		}

		static void OnPrimaryLeave(Object^ sender, EventArgs^)
		{
			Button^ b = dynamic_cast<Button^>(sender);
			if (b != nullptr) b->BackColor = Dark();
		}
	};
}
