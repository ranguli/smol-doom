//
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//

#ifndef TXT_TABLE_H
#define TXT_TABLE_H

/**
 * @file txt_table.h
 *
 * Table widget.
 */

/**
 * Magic value that if used in a table, will indicate that the cell is
 * empty and the widget in the cell to the left can overflow into it.
 */

#define TXT_TABLE_OVERFLOW_RIGHT (&txt_table_overflow_right)

/**
 * Magic value that if used in a table, will indicate that the cell is
 * empty and the widget in the cell above it can overflow down into it.
 */

#define TXT_TABLE_OVERFLOW_DOWN (&txt_table_overflow_down)

/**
 * Magic value that if given to @ref TXT_AddWidget(), will pad out all
 * columns until the end of line.
 */
#define TXT_TABLE_EOL (&txt_table_eol)

/**
 * Indicates an empty space to @ref TXT_AddWidgets(). Equivalent to
 * TXT_AddWidget(table, NULL), except that NULL is used by TXT_AddWidgets()
 * to indicate the end of input.
 */
#define TXT_TABLE_EMPTY (&txt_table_empty)

/**
 * Table widget.
 *
 * A table is a widget that contains other widgets.  It may have
 * multiple columns, in which case the child widgets are laid out
 * in a grid.  Columns automatically grow as necessary, although
 * minimum column widths can be set using @ref TXT_SetColumnWidths.
 *
 * To create a new table, use @ref TXT_NewTable.  It is also
 * possible to use @ref TXT_NewHorizBox to create a table, specifying
 * widgets to place inside a horizontal list.  A vertical list is
 * possible simply by creating a table containing a single column.
 */

typedef struct txt_table_s txt_table_t;

#include "txt_widget.h"

struct txt_table_s
{
    txt_widget_t widget;

    // Widgets in this table
    // The widget at (x,y) in the table is widgets[columns * y + x]
    txt_widget_t **widgets;
    int num_widgets;

    // Number of columns
    int columns;

    // Currently selected:
    int selected_x;
    int selected_y;
};

extern txt_widget_class_t txt_table_class;
extern txt_widget_t txt_table_overflow_right;
extern txt_widget_t txt_table_overflow_down;
extern txt_widget_t txt_table_eol;
extern txt_widget_t txt_table_empty;

void TXT_InitTable(txt_table_t *table, int columns);

/**
 * Create a new table.
 *
 * @param columns       The number of columns in the new table.
 * @return              Pointer to the new table structure.
 */

txt_table_t *TXT_NewTable(int columns);

/**
 * Get the currently selected widget within a table.
 *
 * This function will recurse through subtables if necessary.
 *
 * @param table        The table.
 * @return             Pointer to the widget that is currently selected.
 */

txt_widget_t *TXT_GetSelectedWidget(TXT_UNCAST_ARG(table));

/**
 * Add a widget to a table.
 *
 * Widgets are added to tables horizontally, from left to right.
 * For example, for a table with three columns, the first call
 * to this function will add a widget to the first column, the second
 * call to the second column, the third call to the third column,
 * and the fourth will return to the first column, starting a new
 * row.
 *
 * For adding many widgets, it may be easier to use
 * @ref TXT_AddWidgets.
 *
 * @param table        The table.
 * @param widget       The widget to add.
 */

void TXT_AddWidget(TXT_UNCAST_ARG(table), TXT_UNCAST_ARG(widget));

/**
 * Add multiple widgets to a table.
 *
 * Widgets are added as described in the documentation for the
 * @ref TXT_AddWidget function.  This function adds multiple
 * widgets.  The number of arguments is variable, and the argument
 * list must be terminated by a NULL pointer.
 *
 * @param table        The table.
 */

void TXT_AddWidgets(TXT_UNCAST_ARG(table), ...);

/**
 * Select the given widget that is contained within the specified
 * table.
 *
 * This function will recursively search through subtables if
 * necessary.
 *
 * @param table       The table.
 * @param widget      The widget to select.
 * @return            Non-zero (true) if it has been selected,
 *                    or zero (false) if it was not found within
 *                    this table.
 */

int TXT_SelectWidget(TXT_UNCAST_ARG(table), TXT_UNCAST_ARG(widget));

/**
 * Remove all widgets from a table.
 *
 * @param table    The table.
 */

void TXT_ClearTable(TXT_UNCAST_ARG(table));

/**
 * Hack to move the selection in a table by a 'page', triggered by the
 * scrollpane. This acts as per the keyboard events for the arrows, but moves
 * the selection by at least the specified number of characters.
 *
 * @param table    The table.
 * @param pagex    Minimum distance to move the selection horizontally.
 * @param pagey    Minimum distance to move the selection vertically.
 * @return         Non-zero if the selection has been changed.
 */

int TXT_PageTable(TXT_UNCAST_ARG(table), int pagex, int pagey);

#endif /* #ifndef TXT_TABLE_T */


