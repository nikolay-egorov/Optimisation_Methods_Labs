#include <iostream>
#include <fstream>
#include <string>

#include "Input.h"
#include "Out.h"

void Input::get_data_from_user()
{
	if (!_out.stdin_isatty)
		_out.can_output = false;

	setNumOfSourceVars();
	alloc_memory(numOfSourceVars);
	setFactorsOfTargetFunctionVars();
	setWayOfTargetFunction();
	setFactorsOfSystemVars();
	setFreeMembersOfSystem();

	if (!_out.stdin_isatty)
		_out.can_output = true;
}

void Input::setFreeMembersOfSystem()
{
	for (int i = 0; i < numOfSourceVars; ++i)
	{
		_out << std::cout << "������� �������� ���������� ����� ��� " << i + 1 << "-�� �����������: ";
		std::cin >> freeMembersOfSystem[i];
	}
	_out << std::cout << "\n";
}

void Input::setFactorsOfSystemVars()
{
	int i, j;

	for (i = 0; i < numOfSourceVars; ++i)
	{
		for (j = 0; j < numOfSourceVars; ++j)
		{
			_out << std::cout << "������� ����������� ��� X" << j + 1 << " ��� " << i + 1 << "-�� �����������: ";
			std::cin >> (*factorsOfSystemVars)[i][j];
		}
		_out << std::cout << "\n";
	}
}

void Input::setFactorsOfTargetFunctionVars()
{
	_out << std::cout << "\n";
	for (int i = 0; i < numOfSourceVars; ++i)
	{
		_out << std::cout << "������� ����������� ������� ������� ��� X" << i + 1 << ": ";
		std::cin >> factorsOfTargetFunctionVars[i];
	}
	_out << std::cout << "\n";
}

void Input::setNumOfSourceVars()
{
	for (numOfSourceVars = 0; numOfSourceVars <= 0;) {
		_out << std::cout << "������� ���������� �������� ���������� ������ (> 0): ";
		std::cin >> numOfSourceVars;
	}
}

void Input::setWayOfTargetFunction()
{
	std::string MaxOrMin;

	while (MaxOrMin.compare("max") != 0 && MaxOrMin.compare("min")) {
		_out << std::cout << "������� ����������� ������� ������� (max, min): ";
		std::cin >> MaxOrMin;
		if (MaxOrMin.compare("max") == 0)
			wayOfTargetFunction = true;
		else if (MaxOrMin.compare("min") == 0)
			wayOfTargetFunction = false;
	}
	_out << std::cout << "\n";
}

void Input::alloc_memory(unsigned int vars)
{
	freeMembersOfSystem = new double[vars];
	factorsOfSystemVars = new matrix(vars, vars);
	factorsOfTargetFunctionVars = new double[vars];
}
