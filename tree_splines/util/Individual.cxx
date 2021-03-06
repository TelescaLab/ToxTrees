/*
 * observation.cpp
 *
 *  Created on: 13 juil. 2011
 *      Author
 */


#include "Individual.h"

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace nsTreeSplines;

#define IND nsTreeSplines::Individual

IND::Individual (Params * param) throw ()
{
	m_Params = param;
	int size = m_Params->nb_dose * m_Params->nb_time * m_Params->nb_repeat;
	m_Array = new double [size];
	for (int i = 0; i < size; i++)
		m_Array[i] = 0;
	m_Id = -1;
}

IND::Individual (Params * param, const int & id) throw ()
{
	m_Params = param;
	int size = m_Params->nb_dose * m_Params->nb_time * m_Params->nb_repeat;
	m_Array = new double [size];
	for (int i = 0; i < size; i++)
		m_Array[i] = 0;
	m_Id = id;
}

IND::Individual (IND * individual) throw ()
{
	m_Params = individual->GetParams();
	int size = m_Params->nb_dose * m_Params->nb_time * m_Params->nb_repeat;
	m_Array = new double [size];
	m_Id = individual->GetId();

	for (int i = 0; i < size; i++)
		m_Array[i] = individual->GetValueAt (i);
}

IND::~Individual() throw()
{
	if (m_Array != NULL)
	{
		delete [] m_Array;
		m_Array = NULL;
	}
}

std::ostream& nsTreeSplines::operator<< (std::ostream & os, nsTreeSplines::Individual * individual) throw ()
{
	os << "id (" << individual->GetId() << ") ";
	for (int i=0; i< individual->GetParams()->nb_dose ; i++)
	{
		for (int j = 0; j < individual->GetParams()->nb_time; j++)
		{
			for (int k = 0; k < individual->GetParams()->nb_repeat; k++)
				os << (*individual)(i,j,k) << " ";
			os << endl;
		}
	}
	return os;
}

#undef IND
