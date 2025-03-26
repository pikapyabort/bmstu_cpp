#ifndef MESH_LOADER_ANEUMESHLOADER_H
#define MESH_LOADER_ANEUMESHLOADER_H
#include "MeshLoader.h"

class AneuMeshLoader : public MeshLoader {
public:
    void loadMesh(const std::string&) override; //Данный класс должен обеспечивать загрузку сетки из формата .aneu.
    //Предусмотреть возможность консольного запуска бинарного файла и передачи имени загружаемого файла в параметрах командной строки.
};


#endif //MESH_LOADER_ANEUMESHLOADER_H
