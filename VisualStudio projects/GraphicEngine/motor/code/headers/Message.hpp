
/**
 * @file Message.hpp
 *
 * @brief Clase que almacena los datos de un mensaje para poder ser enviado entre las entidades independientes
 del subsistema ECS
 *
 * @author Esperanza Barcia Ortiz
 * JAN-2021
 */


#pragma once

#include <string>
#include <map>
#include <any>

namespace engine
{
    class Message
    {
    public:

        std::string id;///< Id o nombre del mensaje
        std::map<std::string, std::any> parameters;///<datos del mensaje

    };

}