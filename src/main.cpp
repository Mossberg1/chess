#include <iostream>
#include <string>
#include <stdexcept>

#include "board.hpp"
#include "piece.hpp"

void draw_piece(const Piece& piece);
void draw_board(Board& board);
void switch_player(PieceColor& color);
Position handle_player_input(PieceColor player);
std::string to_string(PieceColor color);

int main() {
    Board* board = new Board();

    bool running = true;
    PieceColor player_turn = PieceColor::White;

    std::cout << "\033[?25l"; 
    std::cout << "\033[2J";

    while (running) {
        std::cout << "\033[H"; 
        draw_board(*board);

        Position move = handle_player_input(player_turn);

        switch_player(player_turn);
    }

    std::cout << "\033[?25h";

    return 0;
}

void draw_board(Board& board) {
    std::cout << "\n";
    
    for (int y = 7; y >= 0; --y) {
        std::cout << y + 1 << " "; 
        
        for (int x = 0; x < 8; ++x) {
            std::optional<Piece> square = board.get_piece(x, y);
            
            if (square.has_value()) {
                std::cout << "[";
                draw_piece(square.value());
                std::cout << "]";
            } else {
                std::cout << "[ ]";
            }
        }
        std::cout << "\n";
    }
    
    std::cout << "   a  b  c  d  e  f  g  h\n\n";
}

void draw_piece(const Piece& piece) {
    char c = ' ';

    switch (piece.get_type()) {
        case PieceType::King:   c = 'K'; break;
        case PieceType::Queen:  c = 'Q'; break;
        case PieceType::Rook:   c = 'R'; break;
        case PieceType::Bishop: c = 'B'; break;
        case PieceType::Knight: c = 'N'; break;
        case PieceType::Pawn:   c = 'P'; break;
    }
    
    // Make Black pieces lowercase
    if (piece.get_color() == PieceColor::Black) {
        c = std::tolower(c);
    }

    std::cout << c;
}

void switch_player(PieceColor& color) {
    color = color == PieceColor::White ? PieceColor::Black : PieceColor::White;
}

Position parse_move(std::string move) {
    if (move.length() != 2) {
        throw std::invalid_argument("Move must have exactly two characters.");
    }

    int x = move[0] - 'a';
    int y = move[1] - '1';

    return { x, y };
}

Position handle_player_input(PieceColor player) {
    std::string move;
    std::cout << to_string(player) << "s turn: ";
    std::cin >> move;
    return parse_move(move);
}

std::string to_string(PieceColor color) {
    return color == PieceColor::White ? "White" : "Black";
}