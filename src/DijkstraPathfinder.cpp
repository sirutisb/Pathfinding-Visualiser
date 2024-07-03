#include "DijkstraPathfinder.h"

std::vector<sf::Vector2i> DijkstraPathfinder::findPath(const sf::Vector2i& start, const sf::Vector2i& end)
{
    std::vector<sf::Vector2i> path;

    //sf::Vector2i currentPos = start;
    //while (currentPos != end) {
    //    std::vector<sf::Vector2i> neighbours = getNeighbours(currentPos);
    //    for (const auto& node : neighbours) {
    //        // if obstacle or visited, continue;
    //        int currentDist = currentNode.getDistance() + 1;
    //        if (currentDist < node.getDistance()) {
    //            node.distance = currentDist;
    //            node.prev = currentNode;
    //            visitedNodes.enqueue(currentNode);
    //        }
    //    }
    //}

    //currentNode = endNode;
    //while (currentNode.prev != startNode) {
    //    currentNode = currentNode.prev;
    //    path.push_front(currentNode);
    //}

    return path;
}
