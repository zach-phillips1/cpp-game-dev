#include "raylib.h"

int main() {
	InitWindow(800, 600, "Hello Raylib!");
	SetTargetFPS(60); // Set the target frames-per-second (FPS)
	while (!WindowShouldClose()) { // Check if the window should close
		BeginDrawing(); // Start drawing
		ClearBackground(RAYWHITE); // Clear the background with a white color
		EndDrawing(); // End drawing
	}
	CloseWindow(); // Close the window and OpenGL context
	return 0;
}