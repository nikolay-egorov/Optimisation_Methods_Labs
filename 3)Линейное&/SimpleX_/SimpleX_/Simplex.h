#include "Plane.h"
#include "user_data.h"
#include "eqparser.h"

 

enum result {
	good_solution, bad_solution, no_solution
};

class Simplex {

public:

	/* ������ �������
	* ������ �������� ������ ������
	* ��� ������� �������� �����
	*/

	Plane* generate_plane(struct user_data::_userdata*);

	/*
	* ������ ������� ������ �������� ���
	* ���� ��������� �������� �����.
	* �� ��� ���������� �������, �������
	* ������ ���������� �������� ��� ���������
	* ��������� �������� ����� � �������� �������.
	*/

	void run();

	/*
	* ������ ������� ��������� ���������� ����
	* �� �������������.
	*/

	bool checkThColumn(Plane*);

	enum result checkPlane(Plane*);

	/*
	* ������ ������� ������ �������� ��������
	* ���������� � �������� �������
	*/

	void setBasisVars(Plane* source, Plane* target);

	/*
	* ������ ������� ���������� ������� ������.
	*/

	void dumpToTableTxt(Plane*, unsigned int iteration, enum result);

	void displayResult(Plane*, unsigned int iteration, enum result);

	/*
	* ������ ������� ������ �������� �������������
	* ��� �������� � �������� ���������� � �������� �������.
	*/

	void setFactorsOfVars(Plane* source, Plane*target);

	/*
	* ������ ������� ������ �������� ������������
	* � ��������� ������ �������� �������.
	*/

	void setIndexString(Plane* source, Plane* target);

	/*
	* ������ ������� ������ �������� �������
	* ���� � �������� �������.
	*/

	void setTargetFunction(Plane* source, Plane* target);

	/*
	* ������ ������� ������ �������� �������������
	* ���������� ������� ����������� �������.
	*/

	void setThColumn(Plane*);

	/*
	* ������ ������� ������ �������� ������� ��������
	* ������� �������� ����� ����������� �������.
	*/

	void setIndexOfLeavingColumn(Plane*);

	/*
	* ������ ������� ������ �������� ������� �������
	* ������ �������� ����� ����������� �������.
	*/

	void setIndexOfLeavingRow(Plane*);

	/*
	* ������ ������� ������� ��������
	* ������������ �������� � ���������� ���
	*/

	void setAllowingMember(Plane*);

private:
	Plane * old_plane, *new_plane;
	int numOfSourceVars;
	eqparser::_limit wayOfTargetFunction;
};
