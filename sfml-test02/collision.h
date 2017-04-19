#pragma once
#include <SFML/Graphics.hpp>

enum collision_state{inside = 1, outside = 0, intersect = 2};

collision_state CircleTest(sf::Vector2f point, sf::Vector2f center, float radius); // ����� � ����������
collision_state CircleTest(sf::Vector2f center1, float radius1, sf::Vector2f center2, float radius2); // ���������� � ����������

collision_state BoundingBoxTest(sf::Vector2f point, sf::FloatRect rect); // ������������� � ��������������
collision_state BoundingBoxTest(sf::FloatRect rect1, sf::FloatRect rect2); // ������������� � ��������������