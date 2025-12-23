#pragma once

#include "DataStructures.h" 

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace System::Threading;
	using namespace System::Diagnostics;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	public ref class Form2 : public System::Windows::Forms::Form
	{
	public:
		Form2(void)
		{
			InitializeComponent();
		}

	protected:
		~Form2()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::MenuStrip^ menuStrip2;
	private: System::Windows::Forms::ToolStripMenuItem^ processToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ trainToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ visualizeBoundariesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ resetNetworkToolStripMenuItem;

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Button^ buttonClear;
	private: System::Windows::Forms::Label^ labelEpoch;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chartLoss;
	private: System::Windows::Forms::CheckBox^ checkBoxMomentum;

	private: System::ComponentModel::Container^ components;

		   List<ClassData^>^ classes;
		   array<Color>^ classColors;
		   Random^ random;

		   int inputSize; //Giriþ Vektörü Boyut 
		   int hiddenSize; //Kaç Tane Gizli Katman Nöronu Olacak
		   int numClasses; //Kaç Tane Sýnýf Olacak Sorusunun Cevabý

		   array<float, 2>^ weights_IH; // weights_IH[0, 0]	weights_IH[0, 1] Ara Katman Nöron Sayýsý Kadar Satýr Olacak
										// weights_IH[1, 0]	weights_IH[1, 1]
										// weights_IH[2, 0]	weights_IH[2, 1]
		  
		   array<float>^ biases_H;      // biases_H[0] biases_H[1] biases_H[2] ... Hidden Size Kadar

		   array<float, 2>^ weights_HO; // weights_HO[0, 0]	weights_HO[0, 1] weights_HO[0, 2] Ara Katman Nöron Sayýsý Kadar Sütun Olacak
										// weights_HO[1, 0]	weights_HO[1, 1] weights_HO[1, 2]
										// weights_HO[2, 0]	weights_HO[2, 1] weights_HO[2, 2]
		  

		   array<float>^ biases_O;		// biases_O[0] biases_O[1] biases_O[2] Sýnýf Sayýsý Kadar


		   array<float, 2>^ velocity_weights_IH;
		   array<float>^ velocity_biases_H;
		   array<float, 2>^ velocity_weights_HO;
		   array<float>^ velocity_biases_O;

		   float learningRate; //Öðrenme Sabiti
		   float momentumFactor;
		   int epochs;

		   Bitmap^ backgroundBitmap; //Arkaplandaki Bitleri Tutan Veri Yapýsý

		   bool IsDesignMode()
		   {
			   return (LicenseManager::UsageMode != LicenseUsageMode::Runtime) || this->DesignMode;
		   }

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			   System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());

			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->menuStrip2 = (gcnew System::Windows::Forms::MenuStrip());
			   this->processToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->trainToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->visualizeBoundariesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->resetNetworkToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			   this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			   this->buttonClear = (gcnew System::Windows::Forms::Button());
			   this->labelEpoch = (gcnew System::Windows::Forms::Label());
			   this->chartLoss = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			   this->checkBoxMomentum = (gcnew System::Windows::Forms::CheckBox());

			   this->menuStrip2->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartLoss))->BeginInit();
			   this->SuspendLayout();

			   this->menuStrip1->Location = System::Drawing::Point(0, 24);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Size = System::Drawing::Size(1100, 24);
			   this->menuStrip1->TabIndex = 0;
			   this->menuStrip1->Text = L"menuStrip1";

			   this->menuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->processToolStripMenuItem });
			   this->menuStrip2->Location = System::Drawing::Point(0, 0);
			   this->menuStrip2->Name = L"menuStrip2";
			   this->menuStrip2->Size = System::Drawing::Size(1100, 24);
			   this->menuStrip2->TabIndex = 1;

			   this->processToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				   this->trainToolStripMenuItem,
					   this->visualizeBoundariesToolStripMenuItem,
					   this->resetNetworkToolStripMenuItem
			   });
			   this->processToolStripMenuItem->Text = L"Ýþlemler (Process)";

			   this->trainToolStripMenuItem->Text = L"1. Aðý Eðit (Train FCN)";
			   this->trainToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form2::trainToolStripMenuItem_Click);

			   this->visualizeBoundariesToolStripMenuItem->Text = L"2. Karar Sýnýrlarýný Görselleþtir";
			   this->visualizeBoundariesToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form2::visualizeBoundariesToolStripMenuItem_Click);

			   this->resetNetworkToolStripMenuItem->Text = L"Aðý Sýfýrla (Noktalarý Koru)";
			   this->resetNetworkToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form2::resetNetworkToolStripMenuItem_Click);

			   this->pictureBox1->BackColor = System::Drawing::SystemColors::ControlLightLight;
			   this->pictureBox1->Location = System::Drawing::Point(12, 60);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(500, 500);
			   this->pictureBox1->TabIndex = 2;
			   this->pictureBox1->TabStop = false;
			   this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form2::pictureBox1_Paint);
			   this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form2::pictureBox1_MouseClick);

			   this->numericUpDown1->Location = System::Drawing::Point(530, 60);
			   this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			   this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			   this->numericUpDown1->Size = System::Drawing::Size(120, 20);
			   this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			   this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Form2::numericUpDown1_ValueChanged);

			   this->listBox1->FormattingEnabled = true;
			   this->listBox1->Location = System::Drawing::Point(530, 90);
			   this->listBox1->Size = System::Drawing::Size(120, 95);

			   this->checkBoxMomentum->AutoSize = true;
			   this->checkBoxMomentum->Location = System::Drawing::Point(530, 200);
			   this->checkBoxMomentum->Name = L"checkBoxMomentum";
			   this->checkBoxMomentum->Size = System::Drawing::Size(104, 17);
			   this->checkBoxMomentum->TabIndex = 16;
			   this->checkBoxMomentum->Text = L"Momentum Kullan";
			   this->checkBoxMomentum->UseVisualStyleBackColor = true;
			   this->checkBoxMomentum->Checked = true;

			   this->buttonClear->Location = System::Drawing::Point(530, 230);
			   this->buttonClear->Text = L"Noktalarý Temizle";
			   this->buttonClear->Size = System::Drawing::Size(120, 30);
			   this->buttonClear->Click += gcnew System::EventHandler(this, &Form2::buttonClear_Click);

			   this->labelEpoch->AutoSize = true;
			   this->labelEpoch->Location = System::Drawing::Point(530, 280);
			   this->labelEpoch->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F, System::Drawing::FontStyle::Bold));
			   this->labelEpoch->Text = L"Durum: Hazýr";

			   chartArea1->Name = L"ChartArea1";
			   chartArea1->AxisX->Title = L"Epoch";
			   chartArea1->AxisY->Title = L"Hata (Loss)";
			   chartArea1->AxisX->MajorGrid->Enabled = false;
			   chartArea1->AxisY->MajorGrid->LineColor = Color::LightGray;
			   chartArea1->AxisY->LabelStyle->Format = "F2";

			   this->chartLoss->ChartAreas->Add(chartArea1);
			   this->chartLoss->Location = System::Drawing::Point(670, 60);
			   this->chartLoss->Name = L"chartLoss";
			   this->chartLoss->Size = System::Drawing::Size(400, 500);
			   this->chartLoss->TabIndex = 15;

			   series1->ChartArea = L"ChartArea1";
			   series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			   series1->Name = L"Error";
			   series1->BorderWidth = 2;
			   series1->Color = Color::Blue;
			   series1->IsVisibleInLegend = false;

			   this->chartLoss->Series->Add(series1);

			   this->ClientSize = System::Drawing::Size(1100, 600);
			   this->Controls->Add(this->checkBoxMomentum);
			   this->Controls->Add(this->chartLoss);
			   this->Controls->Add(this->labelEpoch);
			   this->Controls->Add(this->buttonClear);
			   this->Controls->Add(this->listBox1);
			   this->Controls->Add(this->numericUpDown1);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->menuStrip1);
			   this->Controls->Add(this->menuStrip2);
			   this->MainMenuStrip = this->menuStrip1;
			   this->Text = L"MLP - Momentum & Non-Linear Classification";
			   this->Load += gcnew System::EventHandler(this, &Form2::Form2_Load);

			   this->menuStrip2->ResumeLayout(false);
			   this->menuStrip2->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartLoss))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();
		   }
#pragma endregion

	private: System::Void Form2_Load(System::Object^ sender, System::EventArgs^ e) {
		if (IsDesignMode()) return;
		classColors = gcnew array<Color>{ Color::Red, Color::Blue, Color::Green, Color::Orange, Color::Purple }; //Sýnýflara Ait Renkler, \
		En Fazla 5 Sýnýf Olacak Þekilde Ayarlanmýþ

		classes = gcnew List<ClassData^>(); 
		random = gcnew Random();

		inputSize = 2;
		hiddenSize = 20;
		learningRate = 0.05f;
		momentumFactor = 0.9f;
		epochs = 1000;

		InitializeClasses((int)numericUpDown1->Value);
	}

	private: void InitializeNetworkParameters() {  //Bu fonksiyonda baþlangýç aðýrlýklarý rastgele þekilde atanýyor, momentum aðýrlýklarý atanýyor. \
		Arkaplan ve Grafik Sýfýrlanýyor. Aðý sýfýrla komutu bu fonksiyonu çalýþtýrýyor
		if (IsDesignMode()) return;
		numClasses = classes->Count;

		weights_IH = gcnew array<float, 2>(hiddenSize, inputSize);
		biases_H = gcnew array<float>(hiddenSize);
		weights_HO = gcnew array<float, 2>(numClasses, hiddenSize);
		biases_O = gcnew array<float>(numClasses);

		velocity_weights_IH = gcnew array<float, 2>(hiddenSize, inputSize);
		velocity_biases_H = gcnew array<float>(hiddenSize);
		velocity_weights_HO = gcnew array<float, 2>(numClasses, hiddenSize);
		velocity_biases_O = gcnew array<float>(numClasses);

		for (int i = 0; i < hiddenSize; i++) {
			for (int j = 0; j < inputSize; j++) {
				weights_IH[i, j] = (float)(random->NextDouble() * 2.0 - 1.0) * Math::Sqrt(2.0 / inputSize);
				velocity_weights_IH[i, j] = 0.0f;
			}
			biases_H[i] = 0.0f;
			velocity_biases_H[i] = 0.0f;
		}
		for (int i = 0; i < numClasses; i++) {
			for (int j = 0; j < hiddenSize; j++) {
				weights_HO[i, j] = (float)(random->NextDouble() * 2.0 - 1.0) * Math::Sqrt(2.0 / hiddenSize);
				velocity_weights_HO[i, j] = 0.0f;
			}
			biases_O[i] = 0.0f;
			velocity_biases_O[i] = 0.0f;
		}

		backgroundBitmap = nullptr; // Arka planý sil
		if (chartLoss != nullptr && chartLoss->Series["Error"] != nullptr)
			chartLoss->Series["Error"]->Points->Clear(); // Grafiði sil
	}

	private: void InitializeClasses(int count) { //
		if (IsDesignMode()) return;
		classes->Clear();
		listBox1->Items->Clear();
		int maxCount = Math::Min(count, classColors->Length); //Sýnýf sayýsý renkleri tutan listeden büyükse, sýnýf sayýsý 5 olsun, aksi takdirde \
		ayarladýðýmýz sayý olsun
		for (int i = 0; i < maxCount; i++) {
			ClassData^ cls = gcnew ClassData(i, "Sýnýf " + (i + 1), classColors[i]);
			classes->Add(cls);
			listBox1->Items->Add(cls->Name);
		}
		if (listBox1->Items->Count > 0) listBox1->SelectedIndex = 0;
		InitializeNetworkParameters();
		pictureBox1->Invalidate();
	}

	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (!IsDesignMode()) InitializeClasses((int)numericUpDown1->Value);
	}

	private: System::Void buttonClear_Click(System::Object^ sender, System::EventArgs^ e) {
		for each(ClassData ^ cls in classes) cls->Points->Clear();
		InitializeNetworkParameters();
		pictureBox1->Invalidate();
	}

	private: System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (IsDesignMode() || listBox1->SelectedIndex < 0) return;
		classes[listBox1->SelectedIndex]->Points->Add(e->Location);
		backgroundBitmap = nullptr;
		pictureBox1->Invalidate();
	}

	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		if (IsDesignMode()) return;
		e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

		if (backgroundBitmap != nullptr) e->Graphics->DrawImage(backgroundBitmap, 0, 0);

		float cx = pictureBox1->Width / 2.0f;
		float cy = pictureBox1->Height / 2.0f;
		e->Graphics->DrawLine(Pens::Gray, cx, 0.0f, cx, (float)pictureBox1->Height);
		e->Graphics->DrawLine(Pens::Gray, 0.0f, cy, (float)pictureBox1->Width, cy);

		for each(ClassData ^ cls in classes) {
			Pen^ classPen = gcnew Pen(cls->ClassColor, 2.0f);
			for each(Point p in cls->Points) {
				int s = 4;
				e->Graphics->DrawLine(classPen, p.X, p.Y - s, p.X, p.Y + s);
				e->Graphics->DrawLine(classPen, p.X - s, p.Y, p.X + s, p.Y);
			}
		}
	}

	private: System::Void trainToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		TrainFCN();
	}

	private: System::Void visualizeBoundariesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		GenerateBackgroundVisualization();
	}

	private: System::Void resetNetworkToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		InitializeNetworkParameters(); // Bu metod sadece aðýrlýklarý/biaslarý sýfýrlar ve grafiði temizler.
		pictureBox1->Invalidate();
		labelEpoch->Text = "Að Sýfýrlandý. Eðitime Hazýr.";
	}

	private: float ReLU(float x) { return Math::Max(0.0f, x); }
	private: float ReLU_Derivative(float x) { return x > 0 ? 1.0f : 0.0f; }

	private: array<float>^ Softmax(array<float>^ logits) {
		float maxL = logits[0];
		for (int i = 1; i < logits->Length; i++) if (logits[i] > maxL) maxL = logits[i];
		double sum = 0.0;
		for (int i = 0; i < logits->Length; i++) sum += Math::Exp(logits[i] - maxL);
		array<float>^ probs = gcnew array<float>(logits->Length);
		for (int i = 0; i < logits->Length; i++) probs[i] = (float)(Math::Exp(logits[i] - maxL) / sum);
		return probs;
	}

	private: Tuple<array<float>^, array<float>^>^ ForwardPass(float x, float y) {
		array<float>^ h_out = gcnew array<float>(hiddenSize);
		for (int i = 0; i < hiddenSize; i++)
			h_out[i] = ReLU(weights_IH[i, 0] * x + weights_IH[i, 1] * y + biases_H[i]);

		array<float>^ logits = gcnew array<float>(numClasses);
		for (int i = 0; i < numClasses; i++) {
			float sum = 0.0f;
			for (int j = 0; j < hiddenSize; j++) sum += weights_HO[i, j] * h_out[j];
			logits[i] = sum + biases_O[i];
		}
		return Tuple::Create(h_out, logits);
	}

	private: void TrainFCN() {
		if (IsDesignMode()) return;

		List<PointData^>^ data = gcnew List<PointData^>();
		float cx = pictureBox1->Width / 2.0f;
		float cy = pictureBox1->Height / 2.0f;
		for each(ClassData ^ cls in classes) {
			for each(Point p in cls->Points)
				data->Add(gcnew PointData(cls->Id, 0, (p.X - cx) / cx, (cy - p.Y) / cy)); //Noktalarý merkezi (0, 0) olacak þekilde ayarlýyoruz.
		}
		if (data->Count == 0) return;

		chartLoss->Series["Error"]->Points->Clear();
		bool useMomentum = checkBoxMomentum->Checked;

		for (int epoch = 0; epoch < epochs; epoch++) {
			float totalLoss = 0.0f;

			for (int i = 0; i < data->Count; i++) {  // Daha iyi bir eðitim için her döngüde noktalarý daðýtýyoruz.
				int r = random->Next(i, data->Count);
				PointData^ tmp = data[i]; data[i] = data[r]; data[r] = tmp;
			}

			for each(PointData ^ p in data) {
				auto res = ForwardPass(p->X, p->Y); //Noktalar bu kýsýmda forwardPass yapýlýyor
				array<float>^ h = res->Item1;
				array<float>^ probs = Softmax(res->Item2);

				totalLoss += -Math::Log(Math::Max(1e-9, (double)probs[p->ClassId]));

				array<float>^ d_out = gcnew array<float>(numClasses);
				for (int i = 0; i < numClasses; i++)
					d_out[i] = probs[i] - (i == p->ClassId ? 1.0f : 0.0f);

				array<float>^ d_h = gcnew array<float>(hiddenSize);
				for (int i = 0; i < hiddenSize; i++) {
					float err = 0.0f;
					for (int j = 0; j < numClasses; j++) err += d_out[j] * weights_HO[j, i];
					d_h[i] = err * ReLU_Derivative(h[i]);
				}

				for (int i = 0; i < numClasses; i++) {
					for (int j = 0; j < hiddenSize; j++) {
						float gradient = d_out[i] * h[j];
						if (useMomentum) {
							velocity_weights_HO[i, j] = momentumFactor * velocity_weights_HO[i, j] + learningRate * gradient;
							weights_HO[i, j] -= velocity_weights_HO[i, j];
						}
						else {
							weights_HO[i, j] -= learningRate * gradient;
						}
					}
					float gradBias = d_out[i];
					if (useMomentum) {
						velocity_biases_O[i] = momentumFactor * velocity_biases_O[i] + learningRate * gradBias;
						biases_O[i] -= velocity_biases_O[i];
					}
					else {
						biases_O[i] -= learningRate * gradBias;
					}
				}

				array<float>^ inputs = { p->X, p->Y };
				for (int i = 0; i < hiddenSize; i++) {
					for (int j = 0; j < inputSize; j++) {
						float gradient = d_h[i] * inputs[j];
						if (useMomentum) {
							velocity_weights_IH[i, j] = momentumFactor * velocity_weights_IH[i, j] + learningRate * gradient;
							weights_IH[i, j] -= velocity_weights_IH[i, j];
						}
						else {
							weights_IH[i, j] -= learningRate * gradient;
						}
					}
					float gradBias = d_h[i];
					if (useMomentum) {
						velocity_biases_H[i] = momentumFactor * velocity_biases_H[i] + learningRate * gradBias;
						biases_H[i] -= velocity_biases_H[i];
					}
					else {
						biases_H[i] -= learningRate * gradBias;
					}
				}
			}

			if (epoch % 10 == 0) {
				float avgLoss = totalLoss / data->Count;
				chartLoss->Series["Error"]->Points->AddXY(epoch, avgLoss);
				chartLoss->Update();
				labelEpoch->Text = "Epoch: " + epoch + " | Hata: " + avgLoss.ToString("F3");
				Application::DoEvents();
			}
		}
		labelEpoch->Text = "Eðitim Tamamlandý!";
		//GenerateBackgroundVisualization();
	}

	private: void GenerateBackgroundVisualization() {
		int w = pictureBox1->Width, h = pictureBox1->Height;
		float cx = w / 2.0f, cy = h / 2.0f;

		backgroundBitmap = gcnew Bitmap(w, h, PixelFormat::Format32bppArgb);
		BitmapData^ bmpData = backgroundBitmap->LockBits(System::Drawing::Rectangle(0, 0, w, h), ImageLockMode::WriteOnly, backgroundBitmap->PixelFormat);

		int bytes = Math::Abs(bmpData->Stride) * h;
		array<Byte>^ rgb = gcnew array<Byte>(bytes);
		IntPtr ptr = bmpData->Scan0;

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				auto res = ForwardPass((x - cx) / cx, (cy - y) / cy);
				array<float>^ probs = Softmax(res->Item2);

				int maxC = 0; float maxP = probs[0];
				for (int i = 1; i < numClasses; i++) if (probs[i] > maxP) { maxP = probs[i]; maxC = i; }

				Color c = classColors[maxC];
				int idx = y * bmpData->Stride + x * 4;
				rgb[idx] = c.B; rgb[idx + 1] = c.G; rgb[idx + 2] = c.R; rgb[idx + 3] = 50;
			}
		}
		System::Runtime::InteropServices::Marshal::Copy(rgb, 0, ptr, bytes);
		backgroundBitmap->UnlockBits(bmpData);
		pictureBox1->Invalidate();
	}
	};
}