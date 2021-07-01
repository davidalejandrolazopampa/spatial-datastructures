#include "QuadTree.h"
#include <memory>
#include <iostream>
#include <vector>

namespace utec
{
namespace spatial
{

template<typename Node, typename Rectangle, typename Point>
QuadTree<Node, Rectangle, Point>::QuadTree(){
    this->root=nullptr;
}

template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::insert(Point new_point){
    std::shared_ptr<Node>& target = search(new_point, this->root);
    if(target==nullptr){
        target=std::make_shared<Node>(new_point);
    }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node>& QuadTree<Node, Rectangle, Point>::search(Point target, std::shared_ptr<Node>& node){
    if(node == nullptr){
        return node; //not found
    } else if(node->get_point() == target){
        return node;
    }
    
    auto cur_point = node->get_point();

    const int x=0, y=1;

    if(target.get(x) < cur_point.get(x)){
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NW());
        else
            return search(target, node->SW());
    }else{
        if(target.get(y) > cur_point.get(y))
            return search(target, node->NE());
        else
            return search(target, node->SE());
    }
}

template<typename Node, typename Rectangle, typename Point>
std::vector<Point> QuadTree<Node, Rectangle, Point>::range_new_qd(Rectangle region, std::shared_ptr<Node>& node) {
    //Como es recursivo---
    std::vector<Point> Resultado;
    //TODO
    //Caso base para cuando llegue a una hoja y no tenga hijos
    if (!(node == nullptr)) {
        //Guardo el punto del nodo-
        Point P_temporal = node->get_point(); //Guardar el punto // ver modificacion
        Point oeste_limite = region._min; //minimo
        Point noreste_limite = region._max; // maximo
        //TODO region con un punto minimo y maximo
        if ((oeste_limite.get(0) <= P_temporal.get(0)) && //para el X
            (P_temporal.get(0) <= noreste_limite.get(0)) &&
            (oeste_limite.get(1) <= P_temporal.get(1)) && // para el Y
            (P_temporal.get(1) <= noreste_limite.get(1))) {

            Resultado.push_back(P_temporal);        //TODO Guardo
        }

        //Check other quadrants
        Point point_NW = range_new_qd(region, node->NW());
        if (!(point_NW.size() >= 1)) {} else Resultado.insert(Resultado.end(), point_NW.begin(), point_NW.end());

        Point point_NE = range_new_qd(region, node->NE());
        if (!(point_NE.size() >= 1)) {} else Resultado.insert(Resultado.end(), point_NE.begin(), point_NE.end());

        Point point_SE = range_new_qd(region, node->SE());
        if (!(point_SE.size() >= 1)) {} else Resultado.insert(Resultado.end(), point_SE.begin(), point_SE.end());

        Point point_SW = range_new_qd(region, node->SW());
        if (!(point_SW.size() >= 1)) {} else Resultado.insert(Resultado.end(), point_SW.begin(), point_SW.end());

        return Resultado;
    } else
        return Resultado;
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node> QuadTree<Node, Rectangle, Point>::search(Point target){
    return search(target, this->root);
}

template<typename Node, typename Rectangle, typename Point>
std::vector<Point> QuadTree<Node, Rectangle, Point>::range(Rectangle region){
    //TODO
    // se invoca a otra funcion para ser llamado de forma recursivo, y no modificar el quadtest
    return range_new_qd(region, this->root);
}

template<typename Node, typename Rectangle, typename Point>
Point QuadTree<Node, Rectangle, Point>::nearest_neighbor(Point reference){
    // TODO
}

} //spatial
} //utec
