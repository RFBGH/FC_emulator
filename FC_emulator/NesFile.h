#include "Public.h"

class NesFile{

public:

	UCHAR m_head[16];
	UCHAR* m_rom;
	UCHAR* m_vrom;

	NesFile();

	~NesFile();

	void setHead(UCHAR head[]);
	void newRom(int size);
	void newVRom(int size);
	void setRom(UCHAR* rom, int size);
	void setVRom(UCHAR* vrom, int size);
};