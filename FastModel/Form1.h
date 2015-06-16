#pragma once

#include "engine.h"
#include "func.h"
#include "fileWork.h"


namespace FastModel {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
		FMEngine* engine;
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			engine = new FMEngine;
		    char* fn = engine->getData()->outFileName;
		    clearFile(fn);
		    printHatToFile(fn);
		    printStateToFile(engine->getState(), engine->getData(), fn);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			if (engine)
			{
				delete engine;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  WDEdit;
	private: System::Windows::Forms::TextBox^  MoshEdit;
	private: System::Windows::Forms::TextBox^  T1Edit;



	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  TimeEdit;

	private: System::Windows::Forms::Label^  label4;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->WDEdit = (gcnew System::Windows::Forms::TextBox());
			this->MoshEdit = (gcnew System::Windows::Forms::TextBox());
			this->T1Edit = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->TimeEdit = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(88, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(40, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Время";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 76);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(103, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Частота вращения";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(72, 108);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(24, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Ntk";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// WDEdit
			// 
			this->WDEdit->Location = System::Drawing::Point(144, 72);
			this->WDEdit->Name = L"WDEdit";
			this->WDEdit->Size = System::Drawing::Size(100, 20);
			this->WDEdit->TabIndex = 3;
			// 
			// MoshEdit
			// 
			this->MoshEdit->Location = System::Drawing::Point(144, 104);
			this->MoshEdit->Name = L"MoshEdit";
			this->MoshEdit->Size = System::Drawing::Size(100, 20);
			this->MoshEdit->TabIndex = 4;
			// 
			// T1Edit
			// 
			this->T1Edit->Location = System::Drawing::Point(392, 40);
			this->T1Edit->Name = L"T1Edit";
			this->T1Edit->Size = System::Drawing::Size(100, 20);
			this->T1Edit->TabIndex = 5;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(312, 72);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 6;
			this->button1->Text = L"Расчёт";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// TimeEdit
			// 
			this->TimeEdit->Location = System::Drawing::Point(144, 40);
			this->TimeEdit->Name = L"TimeEdit";
			this->TimeEdit->Size = System::Drawing::Size(100, 20);
			this->TimeEdit->TabIndex = 7;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(304, 44);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(83, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Время расчёта";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(509, 298);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->TimeEdit);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->T1Edit);
			this->Controls->Add(this->MoshEdit);
			this->Controls->Add(this->WDEdit);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 double t1 = 1;
				 System::Double::TryParse(T1Edit->Text,t1);

				 double time0 = engine->getTime();

				 while ((engine->getTime() - time0) < t1-tau)
				 {
					 engine->nextStep();
					 FMEngState* eState = engine->getState();
					 FMEngData* data = engine->getData();

					 TimeEdit->Text = "" + engine->getTime();
					 WDEdit->Text = "" + nd(eState, data);

					 MoshEdit->Text = "" + ntk(eState, data);

					 static int pCnt = 0;  // сколько раз выводили
					 if (pCnt <= (eState->time / tout))
					 {
						pCnt++;
						printStateToFile(eState, data, data->outFileName);
					}
				 }
			 }
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

