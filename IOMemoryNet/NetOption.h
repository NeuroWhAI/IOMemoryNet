#ifndef __NET_OPTION_H__
#define __NET_OPTION_H__

#define GET_FUNC(var, name) auto name() const -> decltype(var) {return var;}
























class NetOption
{
public:
	NetOption();
	virtual ~NetOption();


protected: /* Linker ���� */
	double m_maxFirstLinkerWeight;
	double m_maxLinkerWeight;
	double m_minLinkerWeight;
	double m_hebbRate;


protected: /* Net ���� */
	double m_maxSignalUnit; // �� ���� �������� �̼��� �Է°��� ��ȭ�� ���ο� ����� ������.


public:
	GET_FUNC(m_maxFirstLinkerWeight, getMaxFirstLinkerWeight);
	GET_FUNC(m_maxLinkerWeight, getMaxLinkerWeight);
	GET_FUNC(m_minLinkerWeight, getMinLinkerWeight);
	GET_FUNC(m_hebbRate, getHebbRate);


public:
	GET_FUNC(m_maxSignalUnit, getMaxSignalUnit);
};

#undef GET_FUNC
#endif