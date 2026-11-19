#ifndef CLASS_TABLE_HPP
#define CLASS_TABLE_HPP

#include <iostream>
#include <map>
#include <vector>

#include "../Global/Unicode.hpp"
#include "Color.hpp"
#include "String.hpp"
#include "Util.hpp"

class Table {
   public:
    enum class Align { Right, Center, Left };
    enum class PanelZone { Right, Left };

    Table() {}
    Table(std::string title, std::string subtitle = "") {
        this->title = title;
        this->subtitle = subtitle;
    }

    void add_to_menu(const std::string& content, short width,
                     Align align = Align::Left) {}

    void add_column(const std::string& title, short width,
                    Align align = Align::Left) {
        if (width < title.size()) {
            width += title.size() - width;
        }

        this->total_width += (1 + width);
        this->column_width.push_back(width);
        this->columns.insert(
            {this->total_columns, {{title, {width, (short)align}}}});
        this->total_columns++;
    }

    void add_row(std::vector<std::string> row, Align align = Align::Left) {
        if (row.size() != total_columns) return;

        bool need_new_row = false;
        std::vector<std::string> buffer;
        for (short index = 0; index < row.size(); index++) {
            if (row.at(index).size() >
                get_width_in_colored_text(row.at(index),
                                          column_width.at(index))) {
                buffer.push_back(
                    row.at(index).substr(this->column_width.at(index)));
                need_new_row = true;

                row.at(index) =
                    row.at(index).substr(0, this->column_width.at(index));
            } else {
                buffer.push_back("");
            }
        }

        if (row.size() == total_columns) {
            this->rows.insert({this->raw_index, {{row, align}}});
            this->raw_index++;
        }
        if (need_new_row) {
            add_row(buffer);
        }
    }

    void print_menu() {
        print_menu_column();
        print_row();
    }
    void print_table() {
        print_column();
        print_row();
    }

    void panel(const std::vector<std::string>& main_panel, short width,
               Align main_align = Align::Left) {
        std::cout << TOP_LEFT
                  << Util::generate(HORIZONTAL, width) + TOP_RIGHT + NEW_LINE;

        for (short index = 0; index < main_panel.size(); index++) {
            std::cout << VERTICAL
                      << format_text(main_panel[index], width, main_align)
                      << VERTICAL + NEW_LINE;
        }

        std::cout << BOTTOM_LEFT << Util::generate(HORIZONTAL, width)
                  << BOTTOM_RIGHT << std::endl;
    }

    void panel(const std::vector<std::string>& main_panel, short width,
               const std::vector<std::string>& sub_zone, PanelZone zone,
               Align main_align = Align::Left) {
        short sub_width = get_sub_width(sub_zone);
        short main_width = get_main_width(width, sub_width);

        print_border_line(TOP_LEFT, TOP_RIGHT, main_width, sub_width, zone);
        for (short i = 0; i < short(main_panel.size()); i++) {
            print_panel_row(main_panel[i], get_sub_text(sub_zone, i),
                            main_width, sub_width, zone, main_align);
        }
        print_border_line(BOTTOM_LEFT, BOTTOM_RIGHT, main_width, sub_width,
                          zone);
    }

    void panel(const std::vector<std::string>& main_panel,
               const std::vector<std::string>& left_zone,
               const std::vector<std::string>& right_zone, short width,
               Align align = Align::Left) {
        short left_width = get_sub_width(left_zone);
        short rigth_width = get_sub_width(right_zone);
        short main_width = get_main_width(width, left_width);
        main_width = get_main_width(main_width, rigth_width);

        if (rigth_width > 0) {
            std::cout << make_border(TOP_LEFT, TOP_RIGHT, rigth_width);
        }
        std::cout << make_border(TOP_LEFT, TOP_RIGHT, main_width);

        if (left_width > 0) {
            std::cout << make_border(TOP_LEFT, TOP_RIGHT, left_width);
        }
        std::cout << std::endl;

        for (short i = 0; i < short(main_panel.size()); i++) {
            if (rigth_width > 0) {
                std::cout << make_cell(get_sub_text(right_zone, i), rigth_width,
                                       align);
            }
            std::cout << make_cell(main_panel[i], main_width, align);
            if (left_width > 0) {
                std::cout << make_cell(get_sub_text(left_zone, i), left_width,
                                       align);
            }
            std::cout << std::endl;
        }

        if (rigth_width > 0) {
            std::cout << make_border(BOTTOM_LEFT, BOTTOM_RIGHT, rigth_width);
        }
        std::cout << make_border(BOTTOM_LEFT, BOTTOM_RIGHT, main_width);

        if (left_width > 0) {
            std::cout << make_border(BOTTOM_LEFT, BOTTOM_RIGHT, left_width);
        }
        std::cout << std::endl;
    }

   private:
    std::string title;
    std::string subtitle;

    short total_width = 1;
    std::map<short, std::map<std::string, std::vector<short>>> columns;
    std::map<short, std::map<std::vector<std::string>, Align>> rows;

    short total_columns = 0;
    short raw_index = 0;
    std::vector<short> column_width;

    short get_width_in_colored_text(const std::string& text,
                                    const short& initial_width = 0) {
        short width = initial_width;
        bool in_escape_sequence = false;

        for (size_t i = 0; i < text.size(); ++i) {
            if (text[i] == '\033' || text[i] == '\x1b') {
                if (i + 1 < text.size() && text[i + 1] == '[') {
                    in_escape_sequence = true;
                    // continue;
                }
            }

            if (in_escape_sequence) {
                width++;
                if (text[i] == 'm') {
                    in_escape_sequence = false;
                }
                // continue;
            }
        }

        return width;
    }

    void menu_panel(std::vector<std::string> content, short width,
                    Align align = Align::Left) {
        std::cout << TOP_LEFT
                  << Util::generate(HORIZONTAL, width) + TOP_RIGHT + NEW_LINE;

        for (short index = 0; index < content.size(); index++) {
            std::cout << VERTICAL << format_text(content[index], width, align)
                      << VERTICAL + NEW_LINE;
        }

        std::cout << VERTICAL << Util::generate(' ', width) << VERTICAL
                  << std::endl;
    }

    void draw_top_table() {
        std::cout << TOP_LEFT;
        for (short key = 0; key < this->column_width.size(); key++) {
            std::cout << Util::generate(HORIZONTAL, this->column_width[key]);
            if (key != this->total_columns - 1) std::cout << TOP_T;
        }
        std::cout << TOP_RIGHT << std::endl;
    }

    void draw_top_menu() {
        std::cout << LEFT_T;
        for (short key = 0; key < this->column_width.size(); key++) {
            std::cout << Util::generate(HORIZONTAL, this->column_width[key]);
            if (key != this->total_columns - 1) std::cout << TOP_T;
        }
        std::cout << RIGHT_T << std::endl;
    }

    void draw_botton_table() {
        std::cout << BOTTOM_LEFT;
        for (short key = 0; key < this->column_width.size(); key++) {
            std::cout << Util::generate(HORIZONTAL, this->column_width[key]);
            if (key != this->total_columns - 1) std::cout << BOTTOM_T;
        }
        std::cout << BOTTOM_RIGHT << std::endl;
    }

    void draw_bottom_barrier_table() {
        std::cout << LEFT_T;
        for (short key = 0; key < this->column_width.size(); key++) {
            std::cout << Util::generate(HORIZONTAL, this->column_width[key]);
            if (key != this->total_columns - 1) std::cout << CROSS;
        }
        std::cout << RIGHT_T << std::endl;
    }

    void print_menu_column() {
        menu_panel({title, subtitle}, total_width - 2, Align::Center);
        draw_top_menu();
        std::cout << VERTICAL;
        for (short key = 0; key < this->total_columns; key++) {
            for (const auto& column : columns[key]) {
                std::cout << format_text(column.first, column.second[0],
                                         (Align)column.second[1]);
                if (key != this->total_columns - 1) std::cout << VERTICAL;
            }
        }
        std::cout << VERTICAL << std::endl;

        draw_bottom_barrier_table();
    }

    void print_column() {
        panel({title, subtitle}, total_width - 2, Align::Center);
        draw_top_table();
        std::cout << VERTICAL;
        for (short key = 0; key < this->total_columns; key++) {
            for (const auto& column : columns[key]) {
                std::cout << format_text(column.first, column.second[0],
                                         (Align)column.second[1]);
                if (key != this->total_columns - 1) std::cout << VERTICAL;
            }
        }
        std::cout << VERTICAL << std::endl;

        draw_bottom_barrier_table();
    }

    void print_row() {
        for (short key = 0; key < this->raw_index; key++) {
            std::cout << VERTICAL;
            short index = 0;
            auto row = *rows[key].begin();

            for (const std::string& item : row.first) {
                std::cout << format_text(item, column_width.at(index),
                                         row.second);

                if (index != this->total_columns - 1) std::cout << VERTICAL;
                index++;
            }

            std::cout << VERTICAL << std::endl;
        }

        draw_botton_table();
    }

    std::string format_text(const std::string& text, short width, Align align) {
        std::string new_text = "";
        width = get_width_in_colored_text(text, width);

        switch (align) {
            case Align::Right:
                new_text = String::rjust(text, width);
                break;
            case Align::Center:
                new_text = String::center(text, width);
                break;
            case Align::Left:
                new_text = String::ljust(text, width);
                break;

            default:
                break;
        }
        return new_text;
    }

    // functions handeling panel...
    short get_sub_width(const std::vector<std::string> sub_zone) {
        short longest = 0;
        for (short i = 0; i < short(sub_zone.size()); i++) {
            if ((short)sub_zone[i].size() > longest) {
                longest = (short)sub_zone[i].size();
            }
        }
        if (longest == 0) return 0;
        return longest + 2;
    }

    short get_main_width(short width, short sub_width) {
        if (sub_width > 0) {
            width = width - sub_width - 2;
        }
        if (width < 0) return 0;
        return width;
    }
    std::string make_border(const std::string& left, const std::string& right,
                            short width) {
        return left + Util::generate(HORIZONTAL, width) + right;
    }

    std::string make_cell(const std::string& text, short width, Align align) {
        return std::string(VERTICAL) + format_text(text, width, align) +
               std::string(VERTICAL);
    }

    std::string get_sub_text(const std::vector<std::string>& sub_zone,
                             short index) {
        if (index < (short)sub_zone.size()) {
            return sub_zone[index];
        }
        return "";
    }

    void print_border_line(const std::string& left, const std::string& right,
                           short main_width, short sub_width, PanelZone zone) {
        if (zone == PanelZone::Right && sub_width > 0) {
            std::cout << make_border(left, right, sub_width);
        }
        std::cout << make_border(left, right, main_width);

        if (zone == PanelZone::Left && sub_width > 0) {
            std::cout << make_border(left, right, sub_width);
        }
        std::cout << std::endl;
    }

    void print_panel_row(const std::string& main_text,
                         const std::string& sub_text, short main_width,
                         short sub_width, PanelZone zone, Align align) {
        if (zone == PanelZone::Right && sub_width > 0) {
            std::cout << make_cell(sub_text, sub_width, align);
        }
        std::cout << make_cell(main_text, main_width, align);
        if (zone == PanelZone::Left && sub_width > 0) {
            std::cout << make_cell(sub_text, sub_width, align);
        }
        std::cout << std::endl;
    }
};

#endif  // CLASS_TABLE_HPP