#include "NesFile.h"


NesFile::NesFile(){

	m_rom = NULL;
	m_vrom = NULL;
}

void NesFile::setHead(UCHAR head[]){

	MemCpy(m_head, head, 16);
}

void NesFile::newRom(int size){

	if(m_rom != NULL){
		
		delete[] m_rom;
	}
	m_rom = new UCHAR[size];
}

void NesFile::newVRom(int size){
	
	if(m_vrom != NULL){
		
		delete[] m_vrom;
	}

	m_vrom = new UCHAR[size];
}

void NesFile::setRom(UCHAR* rom, int size){

	newRom(size);
	MemCpy(m_rom, rom, size);
}

void NesFile::setVRom(UCHAR* vrom, int size){

	newVRom(size);
	MemCpy(m_vrom, vrom, size);
}

NesFile::~NesFile(){

	if(m_rom != NULL){
		delete[] m_rom;
	}

	if(m_vrom != NULL){
		delete[] m_vrom;
	}
}