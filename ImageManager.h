#pragma once

#include "config.h"
#include "Singleton.h"
#include <map>

/*
	�迭 : �ε��� -> ������
	stl::vector : �ε��� -> ������
	std::map : Ű -> ������

	����-�� Ʈ�� ���� : ����, ���� ,�˻� O(logN) �ð����⵵
*/

class Image;
class ImageManager : public Singleton<ImageManager>
{

private:
	map<string, Image*> mapImages;
	map<EImageKey, Image*> mapImages2;

public:
	void Init();
	void Release();

	Image* AddImage(const string& key, const wchar_t* filePath, int width, int height,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	Image* AddImage(const string& key, const wchar_t* filePath, int width, int height,
		int maxFrameX, int maxFrameY, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	void DeleteImage(const string& key);

	Image* FindImage(const string& key);

	Image* AddImage(EImageKey key, const wchar_t* filePath, int width, int height,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);
	
	Image* AddImage(EImageKey key, const wchar_t* filePath, int width, int height,
		int maxFrameX, int maxFrameY, bool isTransparent = FALSE, COLORREF transColor = FALSE);
	
	void DeleteImage(EImageKey key);
	
	Image* FindImage(EImageKey key);


};

