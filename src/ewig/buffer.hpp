//
// ewig - an immutable text editor
// Copyright (C) 2017 Juan Pedro Bolivar Puente
//
// This file is part of ewig.
//
// ewig is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ewig is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ewig.  If not, see <http://www.gnu.org/licenses/>.
//

#pragma once

#include <ewig/coord.hpp>

#include <immer/box.hpp>
#include <immer/flex_vector.hpp>
#include <immer/vector.hpp>

#include <boost/optional.hpp>

namespace ewig {

using line = immer::flex_vector<wchar_t>;
using text = immer::flex_vector<line>;

struct file
{
    immer::box<std::string> name;
    text content;
};

struct snapshot
{
    text content;
    coord cursor;
};

struct buffer
{
    file from;
    text content;
    coord cursor;
    coord scroll;
    boost::optional<coord> selection_start;
    immer::vector<snapshot> history;
    boost::optional<std::size_t> history_pos;
};

constexpr auto tab_width = 8;

file load_file(const char* file_name);
file save_file(const char* file_name, text content);
buffer load_buffer(const char* file_name);
buffer save_buffer(buffer buf);
bool is_dirty(const buffer& buf);

coord actual_cursor(buffer buf);
coord actual_display_cursor(const buffer& buf);

index display_line_col(const line& ln, index col);
coord editor_size(coord size);

buffer page_up(buffer buf, coord size);
buffer page_down(buffer buf, coord size);

buffer move_line_start(buffer buf);
buffer move_line_end(buffer buf);
buffer move_buffer_start(buffer buf);
buffer move_buffer_end(buffer buf);

buffer move_cursor_up(buffer buf);
buffer move_cursor_down(buffer buf);
buffer move_cursor_left(buffer buf);
buffer move_cursor_right(buffer buf);

buffer scroll_to_cursor(buffer buf, coord wsize);

buffer delete_char(buffer buf);
buffer delete_char_right(buffer buf);

buffer insert_new_line(buffer buf);
buffer insert_tab(buffer buf);
buffer insert_char(buffer buf, wchar_t value);
buffer insert_text(buffer buf, text value);

std::pair<buffer, text> copy(buffer buf);
std::pair<buffer, text> cut(buffer buf);
std::pair<buffer, text> cut_rest(buffer buf);

buffer select_whole_buffer(buffer buf);
buffer start_selection(buffer buf);
buffer clear_selection(buffer buf);
std::tuple<coord, coord> selected_region(buffer buf);

buffer undo(buffer);
buffer record(buffer before, buffer after);

} // namespace ewig
