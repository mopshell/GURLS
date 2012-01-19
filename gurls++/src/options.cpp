/*
  * The GURLS Package in C++
  *
  * Copyright (C) 2011, IIT@MIT Lab
  * All rights reserved.
  *
 * author:  M. Santoro
 * email:   msantoro@mit.edu
 * website: http://cbcl.mit.edu/IIT@MIT/IIT@MIT.html
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions
  * are met:
  *
  *     * Redistributions of source code must retain the above
  *       copyright notice, this list of conditions and the following
  *       disclaimer.
  *     * Redistributions in binary form must reproduce the above
  *       copyright notice, this list of conditions and the following
  *       disclaimer in the documentation and/or other materials
  *       provided with the distribution.
  *     * Neither the name(s) of the copyright holders nor the names
  *       of its contributors or of the Massacusetts Institute of
  *       Technology or of the Italian Institute of Technology may be
  *       used to endorse or promote products derived from this software
  *       without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  * POSSIBILITY OF SUCH DAMAGE.
  */

#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

#include "options.h"

using namespace std;

namespace gurls{

std::ostream& operator<<(std::ostream& os, GurlsOption& opt) {
	opt.operator <<(os);
	return os;
}



/*
std::ostream& operator<<(std::ostream& os, OptString& opt) {
	return os << opt.getValue();
}

std::ostream& operator<<(std::ostream& os, OptNumber& opt) {
	return os << static_cast<double>(opt.getValue());
}

std::ostream& operator<<(std::ostream& os, OptStringList& opt){
	std::vector<std::string> V = opt.getValue();
	std::vector<std::string>::iterator it = V.begin();
	std::vector<std::string>::iterator end = V.end();
	os << "(" << (*it++);
	while( it != end){
		os << ", " << (*it++);
	}
	os << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, OptNumberList& opt){
	std::vector<double> V = opt.getValue();
	std::vector<double>::iterator it = V.begin();
	std::vector<double>::iterator end = V.end();
	os << "(" << (*it++);
	while( it != end){
		os << ", " << (*it++);
	}
	os << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, OptFunction& opt){
	os << "Pointer to the function " << opt.getName() << " whose signature is: double (*func)(double*, int)" ;
	return os;
}
*/


std::ostream& OptString::operator<<(std::ostream& os){
	return os << this->getValue();
}

std::ostream& OptNumber::operator<<(std::ostream& os) {
	return os << this->getValue();
}

std::ostream& OptStringList::operator<<(std::ostream& os){
	std::vector<std::string> V = this->getValue();
	std::vector<std::string>::iterator it = V.begin();
	std::vector<std::string>::iterator end = V.end();
	os << "(" << (*it++);
	while( it != end){
		os << ", " << (*it++);
	}
	os << ")";
	return os;
}

std::ostream& OptNumberList::operator<<(std::ostream& os){
	std::vector<double> V = this->getValue();
	std::vector<double>::iterator it = V.begin();
	std::vector<double>::iterator end = V.end();
	os << "(" << (*it++);
	while( it != end){
		os << ", " << (*it++);
	}
	os << ")";
	return os;
}

std::ostream& OptFunction::operator<<(std::ostream& os){
	os << "Pointer to the function <" << this->getName()
	   << "> whose signature is: double (*func)(double*, int)" ;
	return os;
}

std::ostream& OptTaskSequence::operator<<(std::ostream& os){
	std::vector<std::string> V = this->tasks;
	std::vector<std::string>::iterator it = V.begin();
	std::vector<std::string>::iterator end = V.end();
	os << "(" << (*it++);
	while( it != end){
		os << ", " << (*it++);
	}
	os << ")";
	return os;
}


double mean(double* v, int n) {
	double m = 0.0;
	for (int i = 0; i < n; i++){
		m+=*v++;
	}
	return m/n;
}

double min(double* v, int n){
	double* m = std::min_element(v,v+n);
	return *m;
}

double max(double* v, int n){
	double* m = std::max_element(v,v+n);
	return *m;
}

double median(double* v, int n){
	std::vector<double> vd(v, v+n);
	sort(vd.begin(), vd.end());
	return *(vd.begin()+vd.size()/2);
}


bool OptTaskSequence::isValid(const std::string & str, std::string& type, std::string& name) {
	size_t found = str.find(gurls::TASKDESC_SEPARATOR);
	if (found==std::string::npos){
		return false;
	}
	type = str.substr(0, found);
	name = str.substr(found+1);
	if (name.find(gurls::TASKDESC_SEPARATOR)!=std::string::npos){
		return false;
	}
	return true;
}



}
