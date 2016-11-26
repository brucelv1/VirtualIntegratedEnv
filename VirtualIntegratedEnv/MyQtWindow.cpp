////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    MyQtWindow.cpp
/// @brief   程序主窗口的源文件    
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "MyQtWindow.h"
#include <dtCore/deltawin.h>
#include <QtOpenGL/QGLWidget>
#include <dtQt/osggraphicswindowqt.h>  //testing qt
#include "VIECoreApp.h"
#include "AddDialog.h"  //点击菜单add，弹出该对话框
#include "SettingsDlg.h"//点击菜单“设置...”，弹出对话框
#include "AddObjDlg.h"  //点击菜单“直接加载->AddObjects”，弹出添加物体对话框
#include "HandConfigFileDlg.h" //点击菜单“直接加载->AddCustomHand...”，弹出选择配置文件对话框
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
	
	//把osg视图窗口从delta3d中提取出来，嵌入到Qt窗口的graphicsView部件中
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
	//获取osg的视图窗口
	dtQt::OSGGraphicsWindowQt* osgGraphWindow = dynamic_cast<dtQt::OSGGraphicsWindowQt*>(mVIECoreApp->GetWindow()->GetOsgViewerGraphicsWindow());
	QWidget* glwidget = osgGraphWindow->GetQGLWidget();

	//为MyQtWindow中的graphicsView部件添加一个子部件：QBoxLayout
	QBoxLayout* blt = new QBoxLayout(QBoxLayout::LeftToRight,graphicsView);

	//把osg视图窗口添加到blt中，这样窗口大小改变的时候，osg视图窗口也会跟着改变
	blt->layout()->addWidget(glwidget);

	return true;
}

void MyQtWindow::on_action_Add_triggered()
{
	AddDialog addDlg(this);
	addDlg.setModal(true);
	//自定义采集该对话框信息的结构体
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

void MyQtWindow::on_actionStart_triggered()  //自动关联槽
{
	actionStart->setEnabled(false);
	actionStop->setEnabled(true);
	
	mVIECoreApp->On_StartTriggered();
}

void MyQtWindow::on_actionStop_triggered()  //自动关联槽
{
	actionStart->setEnabled(true);
	actionStop->setEnabled(false);
	
	mVIECoreApp->On_StopTriggered();
}

void MyQtWindow::on_actionSettings_triggered()  //自动关联槽
{
	SettingsInfoStruct sis;

	SettingsDlg sDlg(mVIECoreApp->strategyList, this);
	sDlg.setModal(true);
	if(sDlg.exec() == QDialog::Accepted)  //点击done，进行消息的接收
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

		actionStart->setEnabled(true);  //策略被成功创建后，才能使用“启动”按钮
	}
	
}

void MyQtWindow::on_actionOpen_triggered()  //自动关联槽
{
	//打开场景，并完成部件关联
	QString fileContext = QDir::currentPath();  //返回应用程序所在目录作为上下文
	QString path = QFileDialog::getOpenFileName(this,QString("Open File"),fileContext,QString("OSG Files(*.osg)"));
	if(!path.isEmpty()) //点击了取消，path是空的；点击打开，path是相应的文件地址
	{
		// tell VIECoreApp to open
	}
}

void MyQtWindow::on_actionSave_triggered()  //自动关联槽
{
	//保存场景，弹窗告知：一定要保存为初始位置！
	QString fileContext = QDir::currentPath();  //返回应用程序所在目录作为上下文
	QString path = QFileDialog::getSaveFileName(this,QString("Save File"),fileContext,QString("OSG Files(*.osg)"));
	
	if(!path.isEmpty()) //点击了取消，path是空的；点击保存，path是相应的文件地址
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
