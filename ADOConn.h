#import "C:/program files/common files/system/ado/msado15.dll" no_namespace rename("EOF","adoEOF")
#pragma once

class CADOConn
{
public:
	CADOConn(void);
	~CADOConn(void);

public:
	//���һ��ָ��Connection�����ָ��:
	_ConnectionPtr m_pConnection;
	//���һ��ָ��Recordset�����ָ��:
	_RecordsetPtr m_pRecordset;
	// ���巽��
public:
	// ��ʼ�����������ݿ�
	void OnInitADOConn();
	// ִ�в�ѯ
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);
	// ִ��SQL��䣬Insert Update _variant_t
	BOOL ExecuteSQL(_bstr_t bstrSQL);
	void ExitConnect();
};