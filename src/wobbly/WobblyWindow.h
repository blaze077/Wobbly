/*

Copyright (c) 2015, John Smith

Permission to use, copy, modify, and/or distribute this software for
any purpose with or without fee is hereby granted, provided that the
above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

*/


#ifndef WOBBLYWINDOW_H
#define WOBBLYWINDOW_H


#include <QCheckBox>
#include <QCloseEvent>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QSettings>
#include <QSignalMapper>
#include <QSlider>
#include <QSpinBox>
#include <QStringListModel>

#include <VapourSynth.h>
#include <VSScript.h>

#include "DockWidget.h"
#include "ImportWindow.h"
#include "ListWidget.h"
#include "PresetTextEdit.h"
#include "TableWidget.h"
#include "WobblyProject.h"


#define NUM_THUMBNAILS 3


class WobblyWindow : public QMainWindow {
    Q_OBJECT

public:
    WobblyWindow();

private:
    // Menus.

    QMenu *tools_menu;

    QMenu *recent_menu;



    // Widgets.

    DockWidget *details_dock;
    QLabel *frame_label;
    QLabel *thumb_labels[NUM_THUMBNAILS];
    QSlider *frame_slider;

    QLabel *frame_num_label;
    QLabel *time_label;
    QLabel *matches_label;
    QLabel *section_label;
    QLabel *custom_list_label;
    QLabel *freeze_label;
    QLabel *decimate_metric_label;
    QLabel *mic_label;
    QLabel *combed_label;

    QLabel *selected_preset_label;
    QLabel *selected_custom_list_label;
    QLabel *zoom_label;

    DockWidget *crop_dock;
    QSpinBox *crop_spin[4];
    QGroupBox *crop_box;
    QCheckBox *crop_early_check;
    QSpinBox *resize_spin[2];
    QGroupBox *resize_box;
    QComboBox *resize_filter_combo;
    QGroupBox *depth_box;
    QComboBox *depth_bits_combo;
    QComboBox *depth_dither_combo;


    DockWidget *preset_dock;
    QComboBox *preset_combo;
    PresetTextEdit *preset_edit;

    DockWidget *pattern_dock;
    QLineEdit *match_pattern_edit;
    QLineEdit *decimation_pattern_edit;

    DockWidget *sections_dock;
    TableWidget *sections_table;
    QGroupBox *short_sections_box;
    QSpinBox *short_sections_spin;

    DockWidget *cl_dock;
    TableWidget *cl_table;
    QMenu *cl_send_range_menu;
    QMenu *cl_copy_range_menu;

    QButtonGroup *frame_rates_buttons;
    DockWidget *frame_rates_dock;
    TableWidget *frame_rates_table;

    DockWidget *frozen_frames_dock;
    TableWidget *frozen_frames_table;

    DockWidget *pg_dock;
    QSpinBox *pg_length_spin;
    QButtonGroup *pg_methods_buttons;
    QButtonGroup *pg_n_match_buttons;
    QButtonGroup *pg_decimate_buttons;
    QButtonGroup *pg_use_patterns_buttons;
    TableWidget *pg_failures_table;

    DockWidget *mic_search_dock;
    QSpinBox *mic_search_minimum_spin;

    DockWidget *c_match_sequences_dock;
    QSpinBox *c_match_minimum_spin;
    TableWidget *c_match_sequences_table;

    DockWidget *fades_dock;
    QSpinBox *fades_gaps_spin;
    TableWidget *fades_table;

    DockWidget *settings_dock;
    QSpinBox *settings_font_spin;
    QCheckBox *settings_compact_projects_check;
    QComboBox *settings_colormatrix_combo;
    QSpinBox *settings_cache_spin;
    TableWidget *settings_shortcuts_table;

    ImportWindow *import_window;


    // Widget-related

    QStringListModel *presets_model;

    QImage splash_image;

    QString window_title;

    QSignalMapper *recent_menu_signal_mapper;


    // Other stuff.

    WobblyProject *project;
    QString project_path;
    QString video_path;

    int current_frame;
    int pending_frame;
    int pending_requests;

    QString match_pattern;
    QString decimation_pattern;

    bool preview;

    struct Shortcut {
        QString keys;
        QString default_keys;
        QString description;
        void (WobblyWindow::* func)();
    };

    std::vector<Shortcut> shortcuts;

    int range_start;
    int range_end;

    int selected_preset;
    int selected_custom_list;

    QSettings settings;


    // VapourSynth stuff.

    const VSAPI *vsapi;
    VSScript *vsscript;
    VSCore *vscore;
    VSNodeRef *vsnode[2];
    const VSFrameRef *vsframes[NUM_THUMBNAILS];


    // Functions

    void createMenu();
    void createShortcuts();
    void resetShortcuts();
    void createFrameDetailsViewer();
    void createCropAssistant();
    void createPresetEditor();
    void createPatternEditor();
    void createSectionsEditor();
    void createCustomListsEditor();
    void createFrameRatesViewer();
    void createFrozenFramesViewer();
    void createPatternGuessingWindow();
    void createMicSearchWindow();
    void createCMatchSequencesWindow();
    void createFadesWindow();
    void createSettingsWindow();
    void drawColorBars();
    void createUI();

    void addRecentFile(const QString &path);

    void readSettings();
    void writeSettings();

    void initialiseVapourSynth();
    void cleanUpVapourSynth();
    void checkRequiredFilters();

    void updatePresets();

    void updateGeometry();
    void updateWindowTitle();
    void initialiseCropAssistant();
    void initialisePresetEditor();
    void updateSectionsEditor();
    void updateCustomListsEditor();
    void updateFrameRatesViewer();
    void initialiseFrameRatesViewer();
    void updateFrozenFramesViewer();
    void updatePatternGuessingWindow();
    void initialisePatternGuessingWindow();
    void initialiseMicSearchWindow();
    void updateCMatchSequencesWindow();
    void initialiseCMatchSequencesWindow();
    void updateFadesWindow();
    void initialiseUIFromProject();

    void evaluateScript(bool final_script);
    void evaluateMainDisplayScript();
    void evaluateFinalScript();
    void requestFrames(int n);
    void updateFrameDetails();

    void errorPopup(const char *msg);

    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void realOpenProject(const QString &path);
    void realOpenVideo(const QString &path);
    void realSaveProject(const QString &path);
    void realSaveScript(const QString &path);
    void realSaveTimecodes(const QString &path);

    void jumpRelative(int offset);

    void zoom(bool in);

    void startRange();
    void finishRange();
    void cancelRange();

    int getSelectedPreset() const;
    void setSelectedPreset(int index);
    void selectPreviousPreset();
    void selectNextPreset();
    void assignSelectedPresetToCurrentSection();

    int getSelectedCustomList() const;
    void setSelectedCustomList(int index);
    void selectPreviousCustomList();
    void selectNextCustomList();
    void addRangeToSelectedCustomList();

public slots:
    void jump1Forward();
    void jump1Backward();
    void jump5Forward();
    void jump5Backward();
    void jump50Forward();
    void jump50Backward();
    void jumpALotForward();
    void jumpALotBackward();

    void jumpToStart();
    void jumpToEnd();

    void jumpToNextSectionStart();
    void jumpToPreviousSectionStart();

    void jumpToPreviousMic();
    void jumpToNextMic();

    void jumpToFrame();

    void freezeForward();
    void freezeBackward();
    void freezeRange();

    void deleteFreezeFrame();

    void cycleMatchBCN();

    void toggleDecimation();

    void toggleCombed();

    void addSection();
    void deleteSection();

    void openProject();
    void openVideo();
    void saveProject();
    void saveProjectAs();
    void saveScript();
    void saveScriptAs();
    void saveTimecodes();
    void saveTimecodesAs();
    void saveScreenshot();
    void importFromProject();
    void quit();
    void showHideFrameDetails();
    void showHideCropping();
    void showHidePresets();
    void showHidePatternEditor();
    void showHideSections();
    void showHideCustomLists();
    void showHideFrameRates();
    void showHideFrozenFrames();
    void showHidePatternGuessing();
    void showHideMicSearchWindow();
    void showHideCMatchSequencesWindow();
    void showHideFadesWindow();

    void presetChanged(const QString &text);
    void presetEdited();

    void resetMatch();
    void resetSection();

    void rotateAndSetPatterns();
    void setMatchPattern();
    void setDecimationPattern();
    void setMatchAndDecimationPatterns();

    void guessCurrentSectionPatternsFromMics();
    void guessProjectPatternsFromMics();
    void guessCurrentSectionPatternsFromMatches();
    void guessProjectPatternsFromMatches();

    void togglePreview();

    void zoomIn();
    void zoomOut();

    void vsLogPopup(int msgType, void *msgv);
    void frameDone(void *framev, int n, void *nodev, void *errorMsgv);
};

#endif // WOBBLYWINDOW_H
