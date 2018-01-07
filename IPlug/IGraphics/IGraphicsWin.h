#pragma once

#include <windows.h>
#include <windowsx.h>
#include <winuser.h>

//TODO: would be nice not to put this here
#ifndef NO_IGRAPHICS
  #ifdef IGRAPHICS_AGG
    #define IGRAPHICS_DRAW_CLASS IGraphicsAGG
    #include "IGraphicsAGG.h"
  #elif defined IGRAPHICS_CAIRO
    #define IGRAPHICS_DRAW_CLASS IGraphicsCairo
    #include "IGraphicsCairo.h"
  #elif defined IGRAPHICS_NANOVG
    #define IGRAPHICS_DRAW_CLASS IGraphicsNanoVG
    #include "IGraphicsNanoVG.h"
  #else
    #define IGRAPHICS_DRAW_CLASS IGraphicsLice
    #include "IGraphicsLice.h"
  #endif
#endif

class IGraphicsWin : public IGRAPHICS_DRAW_CLASS
{
public:
  IGraphicsWin(IPlugBaseGraphics& plug, int w, int h, int fps);
  virtual ~IGraphicsWin();

  void SetHInstance(HINSTANCE hInstance) { mHInstance = hInstance; }

  void ForceEndUserEdit() override;

  void Resize(int w, int h) override;

  void HideMouseCursor() override;
  void ShowMouseCursor() override;
  int ShowMessageBox(const char* str, const char* caption, int type) override;

  void DrawScreen(const IRECT& rect) override;

  void* OpenWindow(void* pParentWnd) override;
  void CloseWindow() override;
  bool WindowIsOpen() override { return (mPlugWnd); }
  
  void UpdateTooltips() {}

  void HostPath(WDL_String& path) override;
  void PluginPath(WDL_String& path) override;
  void DesktopPath(WDL_String& path) override;
  void AppSupportPath(WDL_String& path, bool isSystem = false) override;
  void SandboxSafeAppSupportPath(WDL_String& path) override { AppSupportPath(path, false); }
  bool RevealPathInExplorerOrFinder(WDL_String& path, bool select = false) override;

  void PromptForFile(WDL_String& filename, EFileAction action, WDL_String* pPath, const char* ext) override;
  bool PromptForColor(IColor& color, const char* str) override;

  IPopupMenu* GetItemMenu(long idx, long& idxInMenu, long& offsetIdx, IPopupMenu& baseMenu);
  HMENU CreateMenu(IPopupMenu& menu, long* offsetIdx);

  IPopupMenu* CreateIPopupMenu(IPopupMenu& menu, IRECT& areaRect) override;
  void CreateTextEntry(IControl* pControl, const IText& text, const IRECT& textRect, const char* str, IParam* pParam) override;

  bool OpenURL(const char* url, const char* msgWindowTitle, const char* confirmMsg, const char* errMsgOnFailure);

  // Specialty use!
  void* GetWindow() { return mPlugWnd; }
  HWND GetParentWindow() { return mParentWnd; }
  HWND GetMainWnd();
  void SetMainWndClassName(const char* name) { mMainWndClassName.Set(name); }
//  void GetMainWndClassName(char* name) { strcpy(name, mMainWndClassName.Get()); }
  IRECT GetWindowRECT();
  void SetWindowTitle(const char* str);

  const char* GetGUIAPI() override { return "win32"; };
  
  bool GetTextFromClipboard(WDL_String& str);
protected:
  void SetTooltip(const char* tooltip);
  void ShowTooltip();
  void HideTooltip();

private:
  HINSTANCE mHInstance;
  HWND mPlugWnd, mParamEditWnd, mTooltipWnd;
  IControl* mEdControl;
  IParam* mEdParam;
  WNDPROC mDefEditProc;
  int mParamEditMsg;
  bool mShowingTooltip;
  int mTooltipIdx;
  COLORREF* mCustomColorStorage;

  DWORD mPID;
  HWND mParentWnd, mMainWnd;
  WDL_String mMainWndClassName;

public:
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
  static LRESULT CALLBACK ParamEditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
  static BOOL CALLBACK FindMainWindow(HWND hWnd, LPARAM lParam);
};
