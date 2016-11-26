////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    MyQtWindow.cpp
/// @brief   ���������ڵ�Դ�ļ�    
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "MyQtWindow.h"
#include <dtCore/deltawin.h>
#include <QtOpenGL/QGLWidget>
#include <dtQt/osggraphicswindowqt.h>  //testing qt
#include "VIECoreApp.h"
#include "AddDialog.h"  //����˵�add�������öԻ���
#include "SettingsDlg.h"//����˵�������...���������Ի���
#include "AddObjDlg.h"  //����˵���ֱ�Ӽ���->AddObjects���������������Ի���
#include "HandConfigFileDlg.h" //����˵���ֱ�Ӽ���->AddCustomHand...��������ѡ�������ļ��Ի���
#include <QtCore/QString>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include "InfoStruct.h"
#include <Windows.h>


MyQtWindow::MyQtWindow(VIECoreApp* _vcApp,QMainWindow* parent)
:QMainWindow(parent)
,mVIECoreApp(_vcApp)

{
	setupUi(this);
	this->showMaximized();
	
	//��osg��ͼ���ڴ�delta3d����ȡ������Ƕ�뵽Qt���ڵ�graphicsView������
	addOsgViewerToQtGraphicsView();

	actionStart->setEnabled(false);
	actionStop->setEnabled(false);

	connect(action_Add,SIGNAL(triggered()),this,SLOT(on_action_Add_triggered()));

	this->AddSender(mVIECoreApp);
}

MyQtWindow::~MyQtWindow(void)
{
	this->RemoveSender(mVIECoreApp);

	//The widget's about to be destroyed so we need to tell the GraphicsWindow it's gone (to avoid crash on exit)
	dtQt::OSGGraphicsWindowQt* osgGraphWindow = dynamic_cast<dtQt::OSGGraphicsWindowQt*>(mVIECoreApp->GetWindow()->GetOsgViewerGraphicsWindow());
    if (osgGraphWindow)
    {
       osgGraphWindow->SetQGLWidget(NULL);
    }
}

bool MyQtWindow::addOsgViewerToQtGraphicsView()
{
	//��ȡosg����ͼ����
	dtQt::OSGGraphicsWindowQt* osgGraphWindow = dynamic_cast<dtQt::OSGGraphicsWindowQt*>(mVIECoreApp->GetWindow()->GetOsgViewerGraphicsWindow());
	QWidget* glwidget = osgGraphWindow->GetQGLWidget();

	//ΪMyQtWindow�е�graphicsView�������һ���Ӳ�����QBoxLayout
	QBoxLayout* blt = new QBoxLayout(QBoxLayout::LeftToRight,graphicsView);

	//��osg��ͼ������ӵ�blt�У��������ڴ�С�ı��ʱ��osg��ͼ����Ҳ����Ÿı�
	blt->layout()->addWidget(glwidget);

	return true;
}

void MyQtWindow::on_action_Add_triggered()
{
	AddDialog addDlg(this);
	addDlg.setModal(true);
	//�Զ���ɼ��öԻ�����Ϣ�Ľṹ��
	userAddInfo userdata;
	if(addDlg.exec() == QDialog::Accepted)
	{
		userdata.part = addDlg.partListCombo->currentText().toStdString();
		userdata.name = addDlg.partNameLineEdit->text().toStdString();
		userdata.filename = addDlg.fileNameLineEdit->text().toStdString();
		userdata.x = addDlg.XLineEdit->text().toFloat();
		userdata.y = addDlg.YLineEdit->text().toFloat();
		userdata.z = addDlg.ZLineEdit->text().toFloat();
		userdata.h = addDlg.HLineEdit->text().toFloat();
		userdata.p = addDlg.PLineEdit->text().toFloat();
		userdata.r = addDlg.RLineEdit->text().toFloat();

		if(userdata.filename.empty() == true)
		{
			QMessageBox::warning(NULL, QString("model files"), QString("You didn't fill in any file path!"));
			return;
		}

		//do something to notice VIECoreApp here
		// ...
	}
}

void MyQtWindow::on_actionStart_triggered()  //�Զ�������
{
	actionStart->setEnabled(false);
	actionStop->setEnabled(true);
	
	mVIECoreApp->On_StartTriggered();
}

void MyQtWindow::on_actionStop_triggered()  //�Զ�������
{
	actionStart->setEnabled(true);
	actionStop->setEnabled(false);
	
	mVIECoreApp->On_StopTriggered();
}

void MyQtWindow::on_actionSettings_triggered()  //�Զ�������
{
	SettingsInfoStruct sis;

	SettingsDlg sDlg(mVIECoreApp->strategyList, this);
	sDlg.setModal(true);
	if(sDlg.exec() == QDialog::Accepted)  //���done��������Ϣ�Ľ���
	{
		sis.strategy = sDlg.StrategyBox->currentText().toStdString();
		sis.inputCOM = sDlg.InputBox->currentText().remove(0,3).toInt();
		sis.outputCOM = sDlg.OutputBox->currentText().remove(0,3).toInt();

		if( !mVIECoreApp->On_SettingsInfo(sis))
		{
			QMessageBox msgBox;
			msgBox.setWindowTitle("Strategy Setting");
			msgBox.setIcon(QMessageBox::Icon::Warning);
			msgBox.setInformativeText("The selected strategy has not been loaded!");
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setDefaultButton(QMessageBox::Ok);
			msgBox.exec();
			return;
		}

		actionStart->setEnabled(true);  //���Ա��ɹ������󣬲���ʹ�á���������ť
	}
	
}

void MyQtWindow::on_actionOpen_triggered()  //�Զ�������
{
	//�򿪳���������ɲ�������
	QString fileContext = QDir::currentPath();  //����Ӧ�ó�������Ŀ¼��Ϊ������
	QString path = QFileDialog::getOpenFileName(this,QString("Open File"),fileContext,QString("OSG Files(*.osg)"));
	if(!path.isEmpty()) //�����ȡ����path�ǿյģ�����򿪣�path����Ӧ���ļ���ַ
	{
		// tell VIECoreApp to open
	}
}

void MyQtWindow::on_actionSave_triggered()  //�Զ�������
{
	//���泡����������֪��һ��Ҫ����Ϊ��ʼλ�ã�
	QString fileContext = QDir::currentPath();  //����Ӧ�ó�������Ŀ¼��Ϊ������
	QString path = QFileDialog::getSaveFileName(this,QString("Save File"),fileContext,QString("OSG Files(*.osg)"));
	
	if(!path.isEmpty()) //�����ȡ����path�ǿյģ�������棬path����Ӧ���ļ���ַ
	{
		//tell VIECoreApp to save
	}
}

void MyQtWindow::OnMessage(MessageData* data)
{
}

void MyQtWindow::on_actionSJT_6_triggered()
{
	mVIECoreApp->LoadHand(actionSJT_6->text().toStdString());
}

void MyQtWindow::on_actionSJT_3_triggered()
{
	mVIECoreApp->LoadHand(actionSJT_3->text().toStdString());
}

void MyQtWindow::on_actionBarrett_triggered()
{
	mVIECoreApp->LoadHand(actionBarrett->text().toStdString());
}

void MyQtWindow::on_actionHumanHand_triggered()
{
	mVIECoreApp->LoadHand(actionHumanHand->text().toStdString());
}

void MyQtWindow::on_actionAddObjects_triggered()
{
	AddObjDlg AODlg(this);
	AODlg.setModal(true);
	if(AODlg.exec() == QDialog::Accepted)
	{
		std::string name = AODlg.partNameLineEdit->text().toStdString();
		std::string filename = AODlg.fileNameLineEdit->text().toStdString();

		if (AODlg.PosAttRBtn->isChecked())
		{
			double xyz_hpr[6] = {0};
			xyz_hpr[0] = AODlg.XLineEdit->text().toDouble();
			xyz_hpr[1] = AODlg.YLineEdit->text().toDouble();
			xyz_hpr[2] = AODlg.ZLineEdit->text().toDouble();
			xyz_hpr[3] = AODlg.HLineEdit->text().toDouble();
			xyz_hpr[4] = AODlg.PLineEdit->text().toDouble();
			xyz_hpr[5] = AODlg.RLineEdit->text().toDouble();
			mVIECoreApp->On_AddObjectsDlg(name,filename,xyz_hpr,"HPR");
		}
		if (AODlg.MatRBtn->isChecked())
		{
			double matrixData[16] = {0};
			QStringList tmpDataList = AODlg.MatrixLineEdit->text().split(",");
			if (tmpDataList.size() != 16)
			{
				QMessageBox::warning(NULL, QString("Add Objects..."), QString("The number of inputs doesn't match!"));
				return;
			}
			for (int i=0; i<tmpDataList.size(); i++)
			{
				matrixData[i] = tmpDataList.at(i).toDouble();
			}
			mVIECoreApp->On_AddObjectsDlg(name,filename,matrixData,"MATRIX");
		}
	}
}

void MyQtWindow::on_actionReset_triggered()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Reset");
	msgBox.setIcon(QMessageBox::Icon::Question);
	msgBox.setInformativeText("Are you sure to reset the environment?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Yes);

	if (QMessageBox::Yes == msgBox.exec())
		mVIECoreApp->On_ResetVIE();
}

void MyQtWindow::on_actionAddCustomHand_triggered()
{
	HandConfigFileDlg hcf(this);
	hcf.setModal(true);
	if (hcf.exec() == QDialog::Accepted)
	{
		mVIECoreApp->LoadHand("UserCustom",hcf.PathLine->text().toStdString());
	}
}

void MyQtWindow::on_actionTraining_triggered()
{
	//system("start E:\\My_Cpp_Code\\CPPlearning\\Debug\\TrainModule.exe 7");
	SettingsInfoStruct sis;

	sis.strategy = "CCS_TrainTest";
	sis.inputCOM = 0;
	sis.outputCOM = 0;

	if( !mVIECoreApp->On_SettingsInfo(sis))
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Strategy Setting");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.setInformativeText("The selected strategy has not been loaded!");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		msgBox.exec();

		return;
	}

	// simulate pressing "Start" button
	// the simulation starts from now.
	on_actionStart_triggered();
}

void MyQtWindow::on_actionTesting_triggered()
{

}
