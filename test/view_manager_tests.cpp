#include "../include/view_manager.h"

#include <gtest/gtest.h>

TEST(ViewManagerTests, TabLabelFormatsNameAndKey) {
    ViewManager::View view;
    view.name = "Console";
    view.keyLabel = "F5";
    EXPECT_EQ(ViewManager::tabLabel(view), "Console [F5]");
}

TEST(ViewManagerTests, TabLabelOmitsBracketsWhenNoKey) {
    ViewManager::View view;
    view.name = "Engine";
    view.keyLabel = "";
    EXPECT_EQ(ViewManager::tabLabel(view), "Engine");
}

TEST(ViewManagerTests, CycleNextWrapsAround) {
    ViewManager vm;
    vm.addView("A", "", 0);
    vm.addView("B", "", 0);
    vm.addView("C", "", 0);

    EXPECT_EQ(vm.getCurrentIndex(), 0);
    vm.cycleNext();
    EXPECT_EQ(vm.getCurrentIndex(), 1);
    vm.cycleNext();
    vm.cycleNext();
    EXPECT_EQ(vm.getCurrentIndex(), 0);
}

TEST(ViewManagerTests, SelectByShortcutMatchesRegisteredKey) {
    ViewManager vm;
    vm.addView("Dashboard", "", 0);
    vm.addView("Console", "F5", 116);

    EXPECT_TRUE(vm.selectByShortcut(116));
    EXPECT_EQ(vm.getCurrentIndex(), 1);
    EXPECT_FALSE(vm.selectByShortcut(999));
    EXPECT_EQ(vm.getCurrentIndex(), 1);
}

TEST(ViewManagerTests, SelectChangesCurrentIndexWhenValidAndIgnoresOutOfRange) {
    ViewManager vm;
    vm.addView("A", "", 0);
    vm.addView("B", "", 0);

    vm.select(1);
    EXPECT_EQ(vm.getCurrentIndex(), 1);

    vm.select(-1);
    EXPECT_EQ(vm.getCurrentIndex(), 1);   // out of range: unchanged

    vm.select(5);
    EXPECT_EQ(vm.getCurrentIndex(), 1);   // >= count: unchanged
}

TEST(ViewManagerTests, CycleNextOnEmptyIsSafe) {
    ViewManager vm;
    vm.cycleNext();                        // no views: must not crash / divide-by-zero
    EXPECT_EQ(vm.getCurrentIndex(), 0);
}
