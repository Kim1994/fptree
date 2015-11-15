// Apriori.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ADOconn.h"

CADOConn::CADOConn(void)
{
}

CADOConn::~CADOConn(void)
{
}

/************************************************************************
*Function   : OnInitADOConn
*Description: Init DataBase Connect
*param      : bconString[in] ()
*return     : void
************************************************************************/
void  CADOConn::OnInitADOConn()
{
	// ��ʼ��OLE/COM�⻷�� 
	::CoInitialize(NULL);
	HRESULT hr;

	try
	{
		// ����Connection����,����ͨ�������ļ���ȡ������Ϣ
		hr = m_pConnection.CreateInstance("ADODB.Connection");
		if (SUCCEEDED(hr))
		{
			//m_pConnection->ConnectionTimeout = 600;//�������ӳ�ʱʱ��
			//m_pConnection->CommandTimeout = 120;//����ִ�����ʱʱ��
			m_pConnection->Open("DSN=apriori;Server=localhost;Database=test", "root", "jinhan", adModeUnknown);
		}
	}
	// ��׽�쳣
	catch (_com_error &e)
	{
		// ��ʾ������Ϣ
		cout << e.Description();
	}
}

/************************************************************************
*Function   : GetRecordSet
*Description: Select Data
*param      : bstrSQL[in] SQL
*return     : _RecordsetPtr
************************************************************************/
_RecordsetPtr&  CADOConn::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		// �������ݿ⣬���Connection����Ϊ�գ��������������ݿ�
		if (m_pConnection == NULL)
			OnInitADOConn();
		// ������¼������
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		// ȡ�ñ��еļ�¼
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	// ��׽�쳣
	catch (_com_error e)
	{
		// ��ʾ������Ϣ
	}
	// ���ؼ�¼��
	return m_pRecordset;
}

/************************************************************************
*Function   : ExecuteSQL
*Description: Exec SQL For Insert Update _variant_t
*param      : bstrSQL[in] SQL
*return     : BOOL
************************************************************************/
BOOL CADOConn::ExecuteSQL(_bstr_t bstrSQL)
{
	// _variant_t RecordsAffected;
	try
	{
		// �Ƿ��Ѿ��������ݿ�
		if (m_pConnection == NULL)
			OnInitADOConn();
		// Connection�����Execute����:(_bstr_t CommandText, 
		// VARIANT * RecordsAffected, long Options ) 
		// ����CommandText�������ִ���ͨ����SQL���
		// ����RecordsAffected�ǲ�����ɺ���Ӱ�������, 
		// ����Options��ʾCommandText�����ͣ�adCmdText-�ı����adCmdTable-����
		// adCmdProc-�洢���̣�adCmdUnknown-δ֪
		m_pConnection->Execute(bstrSQL, NULL, adCmdText);
		return true;
	}
	catch (_com_error e)
	{
		return false;
	}
}

/************************************************************************
*Function   : ExitConnect
*Description: Exit Connect DataBase
*param      :
*return     : void
************************************************************************/
void CADOConn::ExitConnect()
{
	// �رռ�¼��������
	if (m_pRecordset != NULL)
	{
		m_pRecordset->Close();
		//m_pRecordset->Release();
	}
	m_pConnection->Close();
	//m_pConnection->Release();
	// �ͷŻ���
	::CoUninitialize();
}



