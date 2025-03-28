#pragma once
#include "config.h"

class Image
{
public:
	enum IMAGE_LOAD_TYPE
	{
		Resource,	// ������Ʈ ��ü�� ���� ��ų �̹���
		File,		// �ܺο��� �ε��� �̹���
		Empty,		// ��ü ������ �̹���
		End
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		// ���ҽ��� ���� ID
		HDC hMemDC;			// �׸��⸦ �ְ��ϴ� ��ü �ڵ�
		HBITMAP hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		HDC hTempDC;
		HBITMAP hTempBit;
		HBITMAP hOldTemp;
		int width;			// �̹��� ���� ũ��
		int height;			// �̹��� ���� ũ��
		BYTE loadType;		// �ε� Ÿ��

		// �ִϸ��̼� ����
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_TYPE::Empty;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
		}
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;
	bool isTransparent;
	COLORREF transColor;

public:
	
	// �� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const wchar_t* filePath, int width, int height,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �̹����� �ε��ϴ� �Լ�
	HRESULT Init(const wchar_t* filePath, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	// ȭ�鿡 ���
	void Render(HDC hdc, int destX = 0, int destY = 0);
	void RenderCenter(HDC hdc, int destX = 0, int destY = 0);

	void FrameRender(HDC hdc, int destX, int destY, int frameX, int frameY, bool isFlip = false);

	//void RenderAtCenter(HDC hdc, int destX, int destY, int frameIndex, bool isFlip = false);
	void RenderHeight(HDC hdc, int destX, int destY, int frameIndex, int totalFrame);

	// �޸� ����
	void Release();

	inline HDC GetMemDC() {
		if (imageInfo)
		{
			return imageInfo->hMemDC;
		}
		return NULL;
	}

	inline int GetMaxFrameX() {return imageInfo->maxFrameX;};
	inline int GetMaxFrameY() {return imageInfo->maxFrameY;};
};

