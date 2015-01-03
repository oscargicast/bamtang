#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>

using namespace std;

// Set here to visualize!
// const string kInitPosition = "7Q/2Rp4/2pN4/p2rp3/P2N4/B1k5/2PpRb2/3K2n1";
const string kInitPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
// Chess pieces available.
const string kChessPieces = "prbnqk";

// Dimensions parametric Chess.
const int kSquareSize = 60; // Change here in order to resize the entire chess.
const float kScaleChessPieces = 0.85; // Relative to the kSquareSize.
const int kScreenWidth = kSquareSize * 8;
const int kScreenHeight = kSquareSize * 10;

// Chessboard Colors.
const GLfloat kBackgroundColor[] = {33.0 / 255.0, 33.0 / 255.0, 33.0 / 255.0, 0.0};
const GLfloat kWhiteSquareColor[] = {117.0 / 255.0, 117.0 / 255.0, 117.0 / 255.0};
const GLfloat kBlackSquareColor[] = {66.00 / 255.0, 66 / 255.0, 66 / 255.0};


// Called when a key is pressed.
void HandleKeypress(unsigned char key, int x, int y) {
  switch (key) {
    case 27: // Escape key.
      exit(0); // Exit the program.
  }
}

// Called when the window is resized. On grounds of simplicity keep it fixed.
void HandleResize(const int w, const int h) {
  glutReshapeWindow(kScreenWidth, kScreenHeight);
}

string GetChessPieceImagePath(char piece) {
  string color = "black";

  if (isupper(piece)) {
    color = "white";
    piece = tolower(piece);
  }

  string filename;
  switch (piece) {
    case 'p': {
      filename = "peon";
      break;
    }
    case 'r': {
      filename = "torre";
      break;
    }
    case 'b': {
      filename = "alfil";
      break;
    }
    case 'n': {
      filename = "caballo";
      break;
    }
    case 'q': {
      filename = "reina";
      break;
    }
    case 'k': {
      filename = "rey";
      break;
    }
  }

  string path = "images/";
  path += filename + "-" + color + ".png";
  return path;
}

void LoadImage(const char chess_piece, const int row = 0, const int col = 0) {
  GLuint texture;
  string image_path = GetChessPieceImagePath(chess_piece);

  int width, height, channels;
  unsigned char *image = SOIL_load_image(
                           image_path.data(),
                           &width, &height, &channels,
                           SOIL_LOAD_RGBA
                         );

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);

  glBindTexture(GL_TEXTURE_2D, texture);

  int max_measure = max(width, height);

  // Scales chess pieces.
  width = kScaleChessPieces * kSquareSize * width / max_measure;
  height = kScaleChessPieces *  kSquareSize * height / max_measure;

  // Places the image in the center of the box (row, column).
  glBegin(GL_QUADS);
  glColor4f(1.0, 1.0, 1.0, 1);

  glTexCoord2f(0, 0);
  glVertex2f(col * kSquareSize + (kSquareSize - width) * 0.5,
             (row + 1) * kSquareSize + (kSquareSize - height) * 0.5);

  glTexCoord2f(0, 1);
  glVertex2f(col * kSquareSize + (kSquareSize - width) * 0.5,
             (row + 1) * kSquareSize + (kSquareSize + height) * 0.5);

  glTexCoord2f(1, 1);
  glVertex2f(col * kSquareSize + (kSquareSize + width) * 0.5,
             (row + 1) * kSquareSize + (kSquareSize + height) * 0.5);

  glTexCoord2f(1, 0);
  glVertex2f(col * kSquareSize + (kSquareSize + width) * 0.5,
             (row + 1) * kSquareSize + (kSquareSize - height) * 0.5);

  glEnd();

}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim))
    elems.push_back(item);
  return elems;
}

vector<string> split(const string &s, char delim) {
  vector<string> elems;
  split(s, delim, elems);
  return elems;
}

// Returns true if the init_position is consistent.
bool ChessPositionValidator(const string init_position) {
  char piece;
  vector<string> chess_rows = split(init_position, '/');
  if (chess_rows.size() != 8)
    return false;

  for (int row = 0; row < chess_rows.size(); row++) {
    int chess_col = 0;
    string chess_row = chess_rows[row];

    for (int j = 0; j < chess_row.length(); j++)
    {
      piece = chess_row[j];

      if (isdigit(piece)) {
        chess_col += piece - '0'; // Cast piece to int and add to col.
        continue;
      }

      if (kChessPieces.find(tolower(piece)) == string::npos) {
        cout << piece << " piece's position is not valid!" << endl;
        return false;
      }

      // If piece is not a number place the piece in the chessboard.
      chess_col++;
    }
    if ( chess_col != 8)
      return false;
  }
  cout << "Your position is acceptable :)" << endl;
  return true;
}

// Draws chess pieces inside the chessboard.
void DrawChessBoard(const string init_position) {
  vector<string> chess_rows = split(init_position, '/');
  char piece;

  for (int row = 0; row < chess_rows.size(); row++) {
    int chess_col = 0;
    string chess_row = chess_rows[row];

    for (int j = 0; j < chess_row.length(); j++)
    {
      piece = chess_row[j];
      if (isdigit(piece)) {
        chess_col += piece - '0'; // Cast piece to int and add to col.
        continue;
      }
      // If piece is not a number place the piece in the chessboard.
      LoadImage(piece, row, chess_col);
      chess_col++;
    }
  }
}

void Render() {
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);

  // Draws the board.
  glColor3f(kWhiteSquareColor[0], kWhiteSquareColor[1], kWhiteSquareColor[2]);
  glRectf(0, kSquareSize, kScreenWidth, kScreenHeight - kSquareSize);

  // Draws the black squares.
  glColor3f(kBlackSquareColor[0], kBlackSquareColor[1], kBlackSquareColor[2]);
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 4; i++) {
      glRectf(
        kSquareSize * (2 * i + j % 2), kScreenHeight - (j + 1) * kSquareSize,
        kSquareSize * (2 * i + j % 2 + 1), kScreenHeight - (j + 2) * kSquareSize
      );
    }
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  DrawChessBoard(kInitPosition);

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glutSwapBuffers();
}

// Sets handler functions for drawing, keypresses, and window resizes.
void InitializeGlutCallbacks()
{
  glutDisplayFunc(Render);
  glutKeyboardFunc(HandleKeypress);
  glutReshapeFunc(HandleResize);
}

bool InitGL()
{
  // Initializes Projection Matrix.
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  // Changes coordinates scale and origin to the top left corner.
  glOrtho(0.0, kScreenWidth, kScreenHeight, 0.0, 1.0, -1.0);

  // Initializes Modelview Matrix.
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  // Sets the background color.
  glClearColor(kBackgroundColor[0], kBackgroundColor[1], kBackgroundColor[2],
               kBackgroundColor[3]);

  // Checks for errors.
  GLenum error = glGetError();
  if (error != GL_NO_ERROR)
  {
    cout << "Error initializing OpenGL!" << gluErrorString(error) << endl;
    return false;
  }

  return true;
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(kScreenWidth, kScreenHeight);
  glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - kScreenWidth) / 2,
                         (glutGet(GLUT_SCREEN_HEIGHT) - kScreenHeight) / 2);

  glutCreateWindow("Chessboard");
  if (!InitGL()) {
    cout << "Unable to initialize graphics library!" << endl;
    return 1;
  }

  InitializeGlutCallbacks();

  cout << "kInitPosition:" << endl;
  cout << kInitPosition << endl;

  if (!ChessPositionValidator(kInitPosition)) {
    cout << "Init position is not valid! :(" << endl;
    exit(0); // Exit the program.
  }

  glutMainLoop();
  return 0;
}