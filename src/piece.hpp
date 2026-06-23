#pragma once

#include <stdexcept>

enum class PieceColor {
    White,
    Black
};

enum class PieceType {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn,
};

struct Position {
    int x;
    int y;
};

struct Move {
    Position from;
    Position to;
};

class Piece {
public:
    Piece(PieceColor color, PieceType type, Position pos) {
        m_color = color;
        m_type = type;
        m_position = pos;
    }

    PieceColor get_color() const {
        return m_color;
    }

    PieceType get_type() const {
        return m_type;
    }

    Position get_position() const {
        return m_position;
    }

    void set_position(int x, int y) {
        if (x < 0 || x > 7 || y < 0 || y > 7) {
            throw std::out_of_range("Out of bounds");
        }

        m_position.x = x;
        m_position.y = y;
    }

private:
    PieceColor m_color;
    PieceType m_type;
    Position m_position;
};