
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2015                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
*	Continued by Esperanza Barcia - APR 2021
*
*  This codes clips a polygon with the viewport to avoid crashes and
*  eliminate parts that do not need to be displayed
*
*/

/*
Rules:
1.Both vertices are inside : Only the second vertex is added to the output list
2.First vertex is outside while second one is inside : Both the point of intersection of the edge with the clip boundary and the second vertex are added to the output list
3.First vertex is inside while second one is outside : Only the point of intersection of the edge with the clip boundary is added to the output list
4.Both vertices are outside : No vertices are added to the output list

*/

#include "Point.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

using namespace sf;
using namespace sample;
using namespace std;

void draw_point(RenderWindow& window, float x, float y, Color color = Color::White)
{
	CircleShape circle(2);

	circle.setFillColor(color);
	circle.setPosition(x, y);

	window.draw(circle);
}

void draw_segment(RenderWindow& window, float x0, float y0, float x1, float y1, Color color = Color::White)
{
	sf::Vertex vertices[2] = { { sf::Vector2f{ x0, y0 }, color }, { sf::Vector2f{ x1, y1 }, color } };

	window.draw(vertices, 2, sf::PrimitiveType::Lines);
}

void draw_segment(RenderWindow& window, const Point2f& p0, const Point2f& p1, Color color = Color::White)
{
	draw_segment(window, p0[0], p0[1], p1[0], p1[1], color);
}

void draw_triangle(RenderWindow& window, const Point2f& p0, const Point2f& p1, const Point2f& p2, Color color = Color::White)
{
	draw_segment(window, p0, p1, color);
	draw_segment(window, p1, p2, color);
	draw_segment(window, p2, p0, color);
}

void draw_polygon(RenderWindow& window, const Point2f* vertices, unsigned number_of_vertices, Color color = Color::White)
{
	if (number_of_vertices >= 2)
	{
		for (unsigned i = 0; i < number_of_vertices - 1; ++i)
		{
			draw_segment(window, vertices[i], vertices[i + 1], color);
		}

		draw_segment(window, vertices[0], vertices[number_of_vertices - 1], color);
	}
}

Point2f get(list<Point2f> _list, int _i)
{
	list<Point2f>::iterator it = _list.begin();
	for (int i = 0; i < _i; i++) {
		++it;
	}
	return *it;
}

bool contains(list<Point2f> _list, Point2f point)
{
	bool res = false;

	for (int i = 0; i < _list.size(); i++)
	{
		if (get(_list, i)[0] == point[0] && get(_list, i)[1] == point[1])
		{
			res = true;
		}
	}
	return res;
}

Point2f CalculateIntersection(Point2f* polygonSegment, Point2f* viewportsegment)
{
	Point2f intersectionPoint = make_point2f(0, 0);

	//Fuente:https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/

	//Ecuación general de la recta A*x + B*y + C = 0
	//Ax0 + By0 = C1
	//AB
	float a = polygonSegment[1][1] - polygonSegment[0][1];//by - ay
	float b = polygonSegment[0][0] - polygonSegment[1][0];//ax - bx
	float c = a * (polygonSegment[0][0]) + b * (polygonSegment[0][1]);

	//CD
	float a1 = viewportsegment[1][1] - viewportsegment[0][1];//by - ay
	float b1 = viewportsegment[0][0] - viewportsegment[1][0];//ax - bx
	float c1 = a1 * (viewportsegment[0][0]) + b1 * (viewportsegment[0][1]);

	float determinant = a * b1 - a1 * b;

	if (determinant != 0)
	{
		float x = (b1 * c - b * c1) / determinant;
		float y = (a * c1 - a1 * c) / determinant;

		intersectionPoint = make_point2f(x, y);
	}
	return intersectionPoint;
}

/// <summary>
/// Comprueba si un vértice están dentro de un área
/// </summary>
/// <param name="vertexA">parámetro de la izquierda, menor que </param>
/// <param name="vertexB">parámetro de la derecha, mayor que</param>
/// <returns></returns>
bool CheckInside(float vertexA, const float vertexB)
{
	if (vertexA < vertexB)
	{
		return false;
	}

	return true;
}



/// <summary>
/// Algoritmo de Sutherland-Hodgman
/// </summary>
const list<Point2f> ClipPolygonWithViewport(RenderWindow& window, const Point2f* polygonVertices, unsigned number_of_vertices, const Point2f* viewportVertices, unsigned viewPort_number_of_vertices)
{
	list<Point2f> output;

	//lado izquierdo
	int side = 0;
	for (size_t i = 0; i < number_of_vertices; i++)
	{
		if (i != number_of_vertices - 1)
		{
			Point2f firstPoint = polygonVertices[i];
			Point2f secondPoint = polygonVertices[i + 1];

			//tenemos en cuenta todos los casos:
			//comparamos la x del poligono con la x del viewport
			//En el caso de tener el primer vértice fuera y el segundo dentro, introducimos el punto de intersección en la lista de salida.
			if (!CheckInside(firstPoint[0], viewportVertices[side][0]) && CheckInside(secondPoint[0], viewportVertices[side][0]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[side + 1] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				output.push_back(secondPoint);

				cout << "primer vértice fuera, segundo dentro";
			}

			//En el caso de tener el primer vértice dentro y el segundo fuera, introducimos el punto de intersección y el segundo vértice en la lista de salida.
			else if (CheckInside(firstPoint[0], viewportVertices[side][0]) && !CheckInside(secondPoint[0], viewportVertices[side][0]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[side + 1] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				/*if (!contains(output, secondPoint))
					output.push_back(secondPoint);*/

				cout << "primer vértice dentro y el segundo fuera";
			}

			//Si ambos vértices están dentro, se añade el segundo vértice a la lista.
			else if (CheckInside(firstPoint[0], viewportVertices[side][0]) && CheckInside(secondPoint[0], viewportVertices[side][0]))
			{
				output.push_back(secondPoint);
				cout << "ambos vértices están dentro";
			}

		
		}
		else
		{
			Point2f firstPoint = polygonVertices[i];
			Point2f secondPoint = polygonVertices[0];

			//tenemos en cuenta todos los casos:
			//comparamos la x del poligono con la x del viewport
			//En el caso de tener el primer vértice fuera y el segundo dentro, introducimos el punto de intersección en la lista de salida.
			if (!CheckInside(firstPoint[0], viewportVertices[side][0]) && CheckInside(secondPoint[0], viewportVertices[side][0]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[side + 1] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				output.push_back(secondPoint);

				cout << "primer vértice fuera, segundo dentro";
			}

			//En el caso de tener el primer vértice dentro y el segundo fuera, introducimos el punto de intersección y el segundo vértice en la lista de salida.
			else if (CheckInside(firstPoint[0], viewportVertices[side][0]) && !CheckInside(secondPoint[0], viewportVertices[side][0]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[side + 1] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);


				/*if (!contains(output, secondPoint))
					output.push_back(secondPoint);*/
				cout << "primer vértice dentro y el segundo fuera";
			}

			//Si ambos vértices están dentro, se añade el segundo vértice a la lista.
			else if (CheckInside(firstPoint[0], viewportVertices[side][0]) && CheckInside(secondPoint[0], viewportVertices[side][0]))
			{
				output.push_back(secondPoint);
				cout << "ambos vértices están dentro";
			}

		}

	}

	list<Point2f> auxOutput = output;
	output.clear();
	//limite de abajo
	side++;
	for (size_t i = 0; i < auxOutput.size(); i++)
	{
		if (i != auxOutput.size() - 1)
		{
			Point2f firstPoint = get(auxOutput, i);
			Point2f secondPoint = get(auxOutput, i + 1);

			//tenemos en cuenta todos los casos:
			//comparamos la x del poligono con la x del viewport
			//En el caso de tener el primer vértice fuera y el segundo dentro, introducimos el punto de intersección en la lista de salida.
			if (!CheckInside(viewportVertices[side][1], firstPoint[1]) && CheckInside(viewportVertices[side][1], secondPoint[1]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[side + 1] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				output.push_back(secondPoint);

				cout << "primer vértice fuera, segundo dentro";
			}
			//En el caso de tener el primer vértice dentro y el segundo fuera, introducimos el punto de intersección y el segundo vértice en la lista de salida.
			else if (CheckInside(viewportVertices[side][1], firstPoint[1]) && !CheckInside(viewportVertices[side][1], secondPoint[1]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[side + 1] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);


				cout << "primer vértice dentro y el segundo fuera";
			}

			//Si ambos vértices están dentro, se añade el segundo vértice a la lista.
			else if (CheckInside(viewportVertices[side][1], firstPoint[1]) && CheckInside(viewportVertices[side][1], secondPoint[1]))
			{
				output.push_back(secondPoint);
				cout << "ambos vértices están dentro";
			}

		}
		else
		{
			Point2f firstPoint = get(auxOutput, i);
			Point2f secondPoint = get(auxOutput, 0);

			//tenemos en cuenta todos los casos:
			//comparamos la x del poligono con la x del viewport
			//En el caso de tener el primer vértice fuera y el segundo dentro, introducimos el punto de intersección en la lista de salida.
			if (!CheckInside(viewportVertices[side][1], firstPoint[1]) && CheckInside(viewportVertices[side][1], secondPoint[1]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[side + 1] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				output.push_back(secondPoint);

				cout << "primer vértice fuera, segundo dentro";
			}
			//En el caso de tener el primer vértice dentro y el segundo fuera, introducimos el punto de intersección y el segundo vértice en la lista de salida.
			else if (CheckInside(viewportVertices[side][1], firstPoint[1]) && !CheckInside(viewportVertices[side][1], secondPoint[1]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[side + 1] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				cout << "primer vértice dentro y el segundo fuera";
			}

			//Si ambos vértices están dentro, se añade el segundo vértice a la lista.
			else if (CheckInside(viewportVertices[side][1], firstPoint[1]) && CheckInside(viewportVertices[side][1], secondPoint[1]))
			{
				output.push_back(secondPoint);
				cout << "ambos vértices están dentro";
			}

		}
	}


	auxOutput.clear();
	auxOutput = output;
	output.clear();
	//lado derecho
	side++;
	for (size_t i = 0; i < auxOutput.size(); i++)
	{
		if (i != auxOutput.size() - 1)
		{
			Point2f firstPoint = get(auxOutput, i);
			Point2f secondPoint = get(auxOutput, i + 1);

			//tenemos en cuenta todos los casos:
			//comparamos la x del poligono con la x del viewport
			//En el caso de tener el primer vértice fuera y el segundo dentro, introducimos el punto de intersección en la lista de salida.
			if (!CheckInside(viewportVertices[side][0], firstPoint[0]) && CheckInside(viewportVertices[side][0], secondPoint[0]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[side + 1] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				output.push_back(secondPoint);

				cout << "primer vértice fuera, segundo dentro";
			}

			//En el caso de tener el primer vértice dentro y el segundo fuera, introducimos el punto de intersección y el segundo vértice en la lista de salida.
			else if (CheckInside(viewportVertices[side][0], firstPoint[0]) && !CheckInside(viewportVertices[side][0], secondPoint[0]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[side + 1] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				cout << "primer vértice dentro y el segundo fuera";
			}

			//Si ambos vértices están dentro, se añade el segundo vértice a la lista.
			else if (CheckInside(viewportVertices[side][0], firstPoint[0]) && CheckInside(viewportVertices[side][0], secondPoint[0]))
			{

				output.push_back(secondPoint);
				cout << "ambos vértices están dentro";
			}

		}
		else
		{
			Point2f firstPoint = get(auxOutput, i);
			Point2f secondPoint = get(auxOutput, 0);

			//tenemos en cuenta todos los casos:
			//comparamos la x del poligono con la x del viewport
			//En el caso de tener el primer vértice fuera y el segundo dentro, introducimos el punto de intersección en la lista de salida.
			if (!CheckInside(viewportVertices[side][0], firstPoint[0]) && CheckInside(viewportVertices[side][0], secondPoint[0]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[side + 1] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				output.push_back(secondPoint);

				cout << "primer vértice fuera, segundo dentro";
			}

			//En el caso de tener el primer vértice dentro y el segundo fuera, introducimos el punto de intersección y el segundo vértice en la lista de salida.
			else if (CheckInside(viewportVertices[side][0], firstPoint[0]) && !CheckInside(viewportVertices[side][0], secondPoint[0]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[side + 1] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				cout << "primer vértice dentro y el segundo fuera";
			}

			//Si ambos vértices están dentro, se añade el segundo vértice a la lista.
			else if (CheckInside(viewportVertices[side][0], firstPoint[0]) && CheckInside(viewportVertices[side][0], secondPoint[0]))
			{
				output.push_back(secondPoint);
				cout << "ambos vértices están dentro";
			}
		}

	}

	auxOutput.clear();
	auxOutput = output;
	output.clear();

	//lado superior
	side++;
	for (size_t i = 0; i < auxOutput.size(); i++)
	{
		if (i != auxOutput.size() - 1)
		{
			Point2f firstPoint = get(auxOutput, i);
			Point2f secondPoint = get(auxOutput, i + 1);

			//tenemos en cuenta todos los casos:
			//comparamos la x del poligono con la x del viewport
			//En el caso de tener el primer vértice fuera y el segundo dentro, introducimos el punto de intersección en la lista de salida.
			if (!CheckInside(firstPoint[1], viewportVertices[side][1]) && CheckInside(secondPoint[1], viewportVertices[side][1]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[0] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				output.push_back(secondPoint);

				cout << "primer vértice fuera, segundo dentro";
			}
			//En el caso de tener el primer vértice dentro y el segundo fuera, introducimos el punto de intersección y el segundo vértice en la lista de salida.
			else if (CheckInside(firstPoint[1], viewportVertices[side][1]) && !CheckInside(secondPoint[1], viewportVertices[side][1]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[0] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				cout << "primer vértice dentro y el segundo fuera";
			}

			//Si ambos vértices están dentro, se añade el segundo vértice a la lista.
			else if (CheckInside(firstPoint[1], viewportVertices[side][1]) && CheckInside(secondPoint[1], viewportVertices[side][1]))
			{
				output.push_back(secondPoint);

				cout << "ambos vértices están dentro";
			}

		}
		else
		{
			Point2f firstPoint = get(auxOutput, i);
			Point2f secondPoint = get(auxOutput, 0);

			//tenemos en cuenta todos los casos:
			//comparamos la x del poligono con la x del viewport
			//En el caso de tener el primer vértice fuera y el segundo dentro, introducimos el punto de intersección en la lista de salida.
			if (!CheckInside(firstPoint[1], viewportVertices[side][1]) && CheckInside(secondPoint[1], viewportVertices[side][1]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[0] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				output.push_back(secondPoint);

				cout << "primer vértice fuera, segundo dentro";
			}
			//En el caso de tener el primer vértice dentro y el segundo fuera, introducimos el punto de intersección y el segundo vértice en la lista de salida.
			else if (CheckInside(firstPoint[1], viewportVertices[side][1]) && !CheckInside(secondPoint[1], viewportVertices[side][1]))
			{
				Point2f polygonSegment[2]{ firstPoint,secondPoint };
				Point2f viewportSegment[2]{ viewportVertices[side],viewportVertices[0] };

				Point2f intersectionPoint = CalculateIntersection(polygonSegment, viewportSegment);

				output.push_back(intersectionPoint);

				cout << "primer vértice dentro y el segundo fuera";
			}

			//Si ambos vértices están dentro, se añade el segundo vértice a la lista.
			else if (CheckInside(firstPoint[1], viewportVertices[side][1]) && CheckInside(secondPoint[1], viewportVertices[side][1]))
			{
				output.push_back(secondPoint);
				cout << "ambos vértices están dentro";
			}

		}
	}
	return output;
}


int main()
{
	constexpr unsigned window_width = 800;
	constexpr unsigned window_height = 600;
	constexpr float  viewport_left = 100;
	constexpr float  viewport_top = 100;
	constexpr float  viewport_width = 600;
	constexpr float  viewport_height = 400;

	RenderWindow window(VideoMode(window_width, window_height), "Polygon clipping", sf::Style::Default, ContextSettings(32));

	window.setVerticalSyncEnabled(true);

	Point2f viewport_p00 = make_point2f(viewport_left, viewport_top);
	Point2f viewport_p01 = make_point2f(viewport_left, viewport_top + viewport_height);
	Point2f viewport_p10 = make_point2f(viewport_left + viewport_width, viewport_top);
	Point2f viewport_p11 = make_point2f(viewport_left + viewport_width, viewport_top + viewport_height);

	Point2f viewport[] = { viewport_p00, viewport_p01, viewport_p11, viewport_p10 };

	Point2f polygon[] = { Point2f({ viewport_width / 2 + 40, 10}),Point2f({ 10 , viewport_height / 2 }),
		Point2f({ viewport_width / 2 + 100, viewport_top + viewport_height + 50 }) };

	Point2f clipped_polygon[10];

	list<Point2f> polygon_list = ClipPolygonWithViewport(window, polygon, 3, viewport, 4);

	int aux = 0;
	for (list<Point2f>::iterator i = polygon_list.begin(); i != polygon_list.end(); i++)
	{
		clipped_polygon[aux] = *i;
		aux++;
	}

	bool running = true;

	do
	{
		// Process window events:

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				running = false;
			}
		}

		// Render:

		window.clear();

		draw_polygon(window, viewport, 4);
		draw_polygon(window, polygon, 3);

		draw_polygon
		(
			window,
			clipped_polygon,
			6,
			Color::Magenta
		);

		window.display();
	} while (running);

	return EXIT_SUCCESS;
}
