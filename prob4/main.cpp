#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <string>

using namespace std;


string kInitPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
const int kSquareSize = 90;
const float kScaleChessPieces = 0.85; // Relative to the kSquareSize.
const int kScreenWidth = kSquareSize * 8;
const int kScreenHeight = kSquareSize * 10;


// Called when a key is pressed.
void HandleKeypress(unsigned char key, int x, int y) {
  switch (key) {
    case 27: // Escape key.
      exit(0); // Exit the program.
  }
}

// Called when the window is resized. On grounds of simplicity keep it fixed.
void HandleResize(int w, int h) {
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

void LoadImage(const char chess_piece, int row = 0, int col = 0) {
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

  // Scaling chess pieces.
  width = kScaleChessPieces * kSquareSize * width / max_measure;
  height = kScaleChessPieces *  kSquareSize * height / max_measure;

  // Placing the image in the center of the box (row, column).
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

void DrawChessBoard(string initPosition =
                      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") {
  LoadImage('r', 0, 0);
  LoadImage('n', 0, 1);
  LoadImage('b', 0, 2);
  LoadImage('q', 0, 3);
  LoadImage('k', 0, 4);
  LoadImage('b', 0, 5);
  LoadImage('n', 0, 6);
  LoadImage('r', 0, 7);

  for (int i = 0; i < 8; i++)
    LoadImage('p', 1, i);

  LoadImage('R', 7, 0);
  LoadImage('N', 7, 1);
  LoadImage('B', 7, 2);
  LoadImage('Q', 7, 3);
  LoadImage('K', 7, 4);
  LoadImage('B', 7, 5);
  LoadImage('N', 7, 6);
  LoadImage('R', 7, 7);

  for (int i = 0; i < 8; i++)
    LoadImage('P', 6, i);
}

void Render() {
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);

  // Print the board.
  glColor3f(117 / 255.0, 117 / 255.0, 117 / 255.0);
  glRectf(0, kSquareSize, kScreenWidth, kScreenHeight - kSquareSize);

  glColor3f(66 / 255.0, 66 / 255.0, 66 / 255.0);
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

// Set handler functions for drawing, keypresses, and window resizes.
void InitializeGlutCallbacks()
{
  glutDisplayFunc(Render);
  glutKeyboardFunc(HandleKeypress);
  glutReshapeFunc(HandleResize);
}

bool InitGL()
{
  // Initialize Projection Matrix.
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  // Change coordinates scale and origin to the top left corner.
  glOrtho(0.0, kScreenWidth, kScreenHeight, 0.0, 1.0, -1.0);

  // Initialize Modelview Matrix.
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  // Initialize clear color.
  glClearColor(33 / 255.0, 33 / 255.0, 33 / 255.0, 0);

  // Check for errors.
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

  glutCreateWindow("Chess Board");
  if (!InitGL()) {
    cout << "Unable to initialize graphics library!" << endl;
    return 1;
  }

  InitializeGlutCallbacks();

  cout << "kInitPosition:" << endl;
  cout << kInitPosition << endl;

  glutMainLoop();
  return 0;
}