#pragma once



/// <summary>
/// ���� ������ ���ν����� ����� Ŭ���� �ν��Ͻ��� �����ɴϴ�.
/// </summary>
///	<param name = "hWnd"> ������ �ڵ��Դϴ�. �ش� ������ �ڵ�� ����� Ŭ���� �ν��Ͻ��� ��ȯ�մϴ�. </param>
/// <returns> ����� Ŭ���� �ν��Ͻ� �����͸� ��ȯ�մϴ�. </returns>
template <typename FrameworkPtr>
FrameworkPtr GetUserDataPtr(HWND hWnd) noexcept
{
	return reinterpret_cast<FrameworkPtr>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
}

/// <summary>
/// ������ ���ν����� Ŭ���� �ν��Ͻ��� �����մϴ�.
/// </summary>
///	<param name = "hWnd"> ������ �ڵ��Դϴ�. �� �ڵ� ������ �����͸� ã�� �� �ְ� �˴ϴ�. </param>
///	<param name = "ptr"> ������ �ڵ�� ����� �������Դϴ�. ��ü�� Ŭ���� �ν��Ͻ��� �����͸� ����մϴ�. </param>
/// <returns> LONG_PTR �������� ������� ��ȯ�մϴ�. </returns>
inline auto SetUserDataPtr(HWND hWnd, LPVOID ptr) noexcept
{
	return ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));
}

/// <summary>
/// Ŭ���̾�Ʈ���� ���� �׷����� ���̸� ������ �ý��� ��� ���� �����Դϴ�.
/// </summary>
int GetMarginWidth();

/// <summary>
/// Ŭ���̾�Ʈ���� ���� �׷����� ���̸� ������ �ý��� ��� ���� �����Դϴ�.
/// </summary>
int GetMarginHeight();

/// <summary>
/// Ŭ���̾�Ʈ���� ���� �׷����� ���̸� ������ �ý��� ��� ���� �����Դϴ�.
/// </summary>
HINSTANCE GetHInstance();

/// <summary>
/// HRESULT�� S_FALSE �� ��� �Էµ� �޽����� �Է��� �޽��� �ڽ��� ����ϸ� true�� ��ȯ�մϴ�.
/// </summary>
///	<param name = "hr"> ���� HRSULT ��ü�Դϴ�. S_FALSE�̸� �޽��� �ڽ��� ����մϴ�. </param>
///	<param name = "msg"> �޽����Դϴ�. ���� �����մϴ�. </param>
///	<param name = "captionMsg"> ĸ�� �����Դϴ�. ���� �����մϴ�. </param>
/// <returns> HRESULT ���� S_FALSE�� ��� true�� ��ȯ�մϴ�. </returns>
inline bool FailureMessage(HRESULT hr, LPCTSTR msg = TEXT(""), LPCTSTR captionMsg = TEXT("Error!"))
{
	if (FAILED(hr))
	{
		MessageBox(NULL, msg, captionMsg, MB_OK);
		return true;
	}
	return false;
}

/// <summary>
/// ���ڷ� ���� �� ���� t ����ŭ ���� �����մϴ�.
/// </summary>
///   <param name = "start"> ���� ���Դϴ�. </param>
///   <param name = "end"> �� ���Դϴ�. </param>
///   <param name = "t"> ���� ���Դϴ�. ��ü�� 0���� 1 ������ �����Դϴ�. </param>
template<typename Ty>
constexpr inline Ty Interpolation(Ty start, Ty end, float t)
{
	return static_cast<Ty>(start * (1.f - t) + end * t);
}



