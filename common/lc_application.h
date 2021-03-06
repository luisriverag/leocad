#pragma once

#include "lc_array.h"

class Project;
class lcPiecesLibrary;

enum class lcShadingMode
{
	Wireframe,
	Flat,
	DefaultLights,
	Full
};

enum class lcViewSphereLocation
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight
};

enum class lcPreviewLocation
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight
};

enum class lcPreviewPosition
{
	Dockable,
	Floating,
	Viewport     // not implemented
};

enum class lcColorTheme
{
	Dark,
	System
};

class lcPreferences
{
public:
	void LoadDefaults();
	void SaveDefaults();
	void SetInterfaceColors(lcColorTheme ColorTheme);

	int mMouseSensitivity;
	lcShadingMode mShadingMode;
	bool mBackgroundGradient;
	quint32 mBackgroundSolidColor;
	quint32 mBackgroundGradientColorTop;
	quint32 mBackgroundGradientColorBottom;
	bool mDrawAxes;
	quint32 mAxesColor;
	quint32 mOverlayColor;
	quint32 mActiveViewColor;
	bool mDrawEdgeLines;
	float mLineWidth;
	bool mAllowLOD;
	float mMeshLODDistance;
	bool mFadeSteps;
	quint32 mFadeStepsColor;
	bool mHighlightNewParts;
	quint32 mHighlightNewPartsColor;
	bool mDrawGridStuds;
	quint32 mGridStudColor;
	bool mDrawGridLines;
	int mGridLineSpacing;
	quint32 mGridLineColor;
	bool mFixedAxes;
	bool mViewSphereEnabled;
	lcViewSphereLocation mViewSphereLocation;
	int mViewSphereSize;
	quint32 mViewSphereColor;
	quint32 mViewSphereTextColor;
	quint32 mViewSphereHighlightColor;
	bool mAutoLoadMostRecent;
	bool mRestoreTabLayout;
	lcColorTheme mColorTheme;

	int mPreviewEnabled;
	quint32 mPreviewActiveColor;
	int mPreviewViewSphereEnabled;
	int mPreviewViewSphereSize;
	lcViewSphereLocation mPreviewViewSphereLocation;
	lcPreviewLocation mPreviewLocation;
	lcPreviewPosition mPreviewPosition;
	int mPreviewSize;
	int mDrawPreviewAxis;
	int mDrawPreviewViewSphere;
};

class lcApplication : public QApplication
{
	Q_OBJECT

public:
	lcApplication(int& Argc, char** Argv);
	~lcApplication();

	void SetProject(Project* Project);
	bool Initialize(QList<QPair<QString, bool>>& LibraryPaths, bool& ShowWindow);
	void Shutdown();
	void ShowPreferencesDialog();
	void SaveTabLayout() const;

	bool LoadPartsLibrary(const QList<QPair<QString, bool>>& LibraryPaths, bool OnlyUsePaths, bool ShowProgress);

	void SetClipboard(const QByteArray& Clipboard);
	void ExportClipboard(const QByteArray& Clipboard);

	Project* mProject;
	lcPiecesLibrary* mLibrary;
	lcPreferences mPreferences;
	QByteArray mClipboard;

protected:
	void UpdateStyle();
	QString GetTabLayoutKey() const;

	QString mDefaultStyle;
};

extern lcApplication* gApplication;

inline lcPiecesLibrary* lcGetPiecesLibrary()
{
	return gApplication->mLibrary;
}

inline Project* lcGetActiveProject()
{
	return gApplication->mProject;
}

inline lcPreferences& lcGetPreferences()
{
	return gApplication->mPreferences;
}
