#pragma once

#include <optional>
#include <stdexcept>

#include "piece.hpp"

class Board {
public:
    Board() {
        initialize_board();
    }

    std::optional<Piece> get_piece(int x, int y) {
        if (x < 0 || x > 7 || y < 0 || y > 7) {
            throw std::out_of_range("Board coordinates are out of bounds.");
        }

        return m_board[x][y];
    }

private:
    static constexpr int WIDTH = 8;
    static constexpr int HEIGHT = 8;
    
    std::optional<Piece> m_board[WIDTH][HEIGHT];

    void initialize_board() {
        // Define order of pieces
        PieceType piece_set[WIDTH] = {
            PieceType::Rook, PieceType::Knight, PieceType::Bishop, PieceType::Queen,
            PieceType::King, PieceType::Bishop, PieceType::Knight, PieceType::Rook
        };

        for (int x = 0; x < WIDTH; x++) { // Places pieces on board
            m_board[x][0] = Piece(PieceColor::White, piece_set[x], {x, 0});
            m_board[x][1] = Piece(PieceColor::White, PieceType::Pawn, {x, 1});

            m_board[x][6] = Piece(PieceColor::Black, PieceType::Pawn, {x, 6});
            m_board[x][7] = Piece(PieceColor::Black, piece_set[x], {x, 7});
        }
    }
};