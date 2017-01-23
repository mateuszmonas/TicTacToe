#include <windows.h>
#include <tchar.h>

bool running = true;
RECT rect;
POINT p;
int plr = 1;
class spots
{
public:
	bool disabled = false;
	bool color = false;
	int player = 0;
	long top;
	long bottom;
	long left;
	long right;
	bool check()
	{
		if (disabled == false)
		{
			player = plr;
			color = true;
			disabled = true;
			return 1;
		}
		else return 0;
	}
}s[9];

void reset()
{
	plr = 1;
	for (int i = 0; i < 9; i++)
	{
		s[i].color = false;
		s[i].disabled = false;
		s[i].player = 0;
	}
}


void SetColor(HDC * hdc, COLORREF * color)
{
	SelectObject(*hdc, GetStockObject(DC_PEN));
	SetDCPenColor(*hdc, *color);
	SelectObject(*hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(*hdc, *color);
}

void DrawLines(HDC * hdc)
{
	COLORREF LinesColor = RGB(255, 255, 255);
	SetColor(&(*hdc), &LinesColor);
	Rectangle(*hdc, rect.right / 3 - 5, rect.top,
		rect.right / 3 + 5, rect.bottom);
	Rectangle(*hdc, 2 * (rect.right / 3) - 5, rect.top,
		2 * (rect.right / 3) + 5, rect.bottom);
	Rectangle(*hdc, rect.left, rect.bottom / 3 - 5,
		rect.right, rect.bottom / 3 + 5);
	Rectangle(*hdc, rect.left, 2 * (rect.bottom / 3) - 5,
		rect.right, 2 * (rect.bottom / 3) + 5);
}

void SetSize()
{
	s[0].top = rect.top;
	s[0].left = rect.left;
	s[0].right = rect.right / 3 - 5;
	s[0].bottom = rect.bottom / 3 - 5;

	s[1].top = rect.top;
	s[1].left = rect.right / 3 + 5;
	s[1].right = 2 * (rect.right / 3) - 5;
	s[1].bottom = rect.bottom / 3 - 5;

	s[2].top = rect.top;
	s[2].left = 2 * (rect.right / 3) + 5;
	s[2].right = rect.right;
	s[2].bottom = rect.bottom / 3 - 5;

	s[3].top = rect.bottom / 3 + 5;
	s[3].left = rect.left;
	s[3].right = rect.right / 3 - 5;
	s[3].bottom = 2 * (rect.bottom / 3) - 5;

	s[4].top = rect.bottom / 3 + 5;
	s[4].left = rect.right / 3 + 5;
	s[4].right = 2 * (rect.right / 3) - 5;
	s[4].bottom = 2 * (rect.bottom / 3) - 5;

	s[5].top = rect.bottom / 3 + 5;
	s[5].left = 2 * (rect.right / 3) + 5;
	s[5].right = rect.right;
	s[5].bottom = 2 * (rect.bottom / 3) - 5;

	s[6].top = 2 * (rect.bottom / 3) + 5;
	s[6].left = rect.left;
	s[6].right = rect.right / 3 - 5;
	s[6].bottom = rect.bottom;

	s[7].top = 2 * (rect.bottom / 3) + 5;
	s[7].left = rect.right / 3 + 5;
	s[7].right = 2 * (rect.right / 3) - 5;
	s[7].bottom = rect.bottom;

	s[8].top = 2 * (rect.bottom / 3) + 5;
	s[8].left = 2 * (rect.right / 3) + 5;
	s[8].right = rect.right;
	s[8].bottom = rect.bottom;
}

bool WhichSpot()
{
	for (int i = 0; i < 9; i++)
	{
		if (((p.x < s[i].right) && (p.x > s[i].left))
			&& ((p.y < s[i].bottom) && (p.y > s[i].top)))
		{
			if (s[i].check()) return 1;
			else return 0;
		}
	}
	return 0;
}

void fill(HDC * hdc)
{
	COLORREF SpotColor;
	for (int i = 0; i < 9; i++)
	{
		if (s[i].color == true)
		{
			if (s[i].player == 1) SpotColor = RGB(255, 0, 0);
			else SpotColor = RGB(0, 255, 0);
			SetColor(&(*hdc), &SpotColor);
			Rectangle(*hdc, s[i].left, s[i].top, s[i].right, s[i].bottom);
		}
	}
}

void Message(HWND * hwnd, int i)
{
	LPCWSTR Message = NULL;
	switch (i)
	{
	case 0:
		Message = L"It Is A Draw\nWould You Like To Play Again?";
		break;
	case 1:
		Message = L"Red Player Has Won\nWould You Like To Play Again?";
		break;
	case 2:
		Message = L"Green Player Has Won\nWould You Like To Play Again?";
		break;
	}
	UINT Choice = MessageBox(*hwnd, Message, (LPCWSTR)L"Winner", MB_YESNO);
	switch (Choice)
	{
	case IDYES:
		reset();
		InvalidateRect(*hwnd, 0, true);
		break;
	case IDNO:
		running = false;
		break;
	}
}

void CheckWinner(HWND * hwnd)
{
	InvalidateRect(*hwnd, 0, true);
	if ((s[0].player == 1 && s[1].player == 1 && s[2].player == 1)
		|| (s[3].player == 1 && s[4].player == 1 && s[5].player == 1)
		|| (s[6].player == 1 && s[7].player == 1 && s[8].player == 1)
		|| (s[0].player == 1 && s[3].player == 1 && s[6].player == 1)
		|| (s[1].player == 1 && s[4].player == 1 && s[7].player == 1)
		|| (s[2].player == 1 && s[5].player == 1 && s[8].player == 1)
		|| (s[0].player == 1 && s[4].player == 1 && s[8].player == 1)
		|| (s[2].player == 1 && s[4].player == 1 && s[6].player == 1))
	{
		Message(&(*hwnd), 1);
		return;
	}
	if ((s[0].player == 2 && s[1].player == 2 && s[2].player == 2)
		|| (s[3].player == 2 && s[4].player == 2 && s[5].player == 2)
		|| (s[6].player == 2 && s[7].player == 2 && s[8].player == 2)
		|| (s[0].player == 2 && s[3].player == 2 && s[6].player == 2)
		|| (s[1].player == 2 && s[4].player == 2 && s[7].player == 2)
		|| (s[2].player == 2 && s[5].player == 2 && s[8].player == 2)
		|| (s[0].player == 2 && s[4].player == 2 && s[8].player == 2)
		|| (s[2].player == 2 && s[4].player == 2 && s[6].player == 2))
	{
		Message(&(*hwnd), 2);
		return;
	}
	if (s[0].disabled == true &&
		s[1].disabled == true &&
		s[2].disabled == true &&
		s[3].disabled == true &&
		s[4].disabled == true &&
		s[5].disabled == true &&
		s[6].disabled == true &&
		s[7].disabled == true &&
		s[8].disabled == true)
	{
		Message(&(*hwnd), 0);
		return;
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 0)));
		DrawLines(&hdc);
		fill(&hdc);

		EndPaint(hwnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		GetCursorPos(&p);
		ScreenToClient(hwnd, &p);
		if (WhichSpot())
		{
			if (plr == 1) plr = 2;
			else plr = 1;
		}
		InvalidateRect(hwnd, 0, true);
		CheckWinner(&hwnd);
		break;
	case WM_RBUTTONDOWN:
		InvalidateRect(hwnd, 0, true);
		break;
	case WM_DESTROY:
	case WM_CLOSE:
	case WM_QUIT:
		running = false;
		break;
	default:
		result = DefWindowProc(hwnd, msg, wParam, lParam);
		break;
	}

	return result;
}


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex = {};

	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &WindowProc;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = _T("Circle  'n' Cross");

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	HWND hwnd = CreateWindow(
		wcex.lpszClassName,
		_T("Circle  'n' Cross"),
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		320, 320,
		0,
		0,
		hInstance,
		0
	);

	if (!hwnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	GetClientRect(hwnd, &rect);
	SetSize();

	MSG Message;
	while (running)
	{
		while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}

	return 0;
}
