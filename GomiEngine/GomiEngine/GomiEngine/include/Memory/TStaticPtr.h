#pragma once
namespace EngineUtilities {
   /**
   * Clase TStaticPtr para manejo de un puntero estático.
   *
   * La clase TStaticPtr gestiona un único objeto estático y proporciona métodos
   * para acceder al objeto, verificar si el puntero es nulo y realizar operaciones
   * básicas de manejo de memoria.
   */
    template<typename T>
    class TStaticPtr
    {
    public:
        // Inicializa el puntero estático al objeto.
        TStaticPtr() = default;

        // Constructor que toma un puntero crudo.
        explicit TStaticPtr(T* rawPtr)
        {
            if (instance != nullptr)
            {
                delete instance;
            }
            instance = rawPtr;
        }

        //  Destructor.
        ~TStaticPtr()
        {
            if (instance != nullptr)
            {
                delete instance;
                instance = nullptr;
            }
        }

        // Obtener el puntero crudo.
        static T* get()
        {
            return instance;
        }

        // Verificar si el puntero es nulo.
        static bool isNull()
        {
            return instance == nullptr;
        }

        // Reiniciar el puntero estático con un nuevo objeto.
        static void reset(T* rawPtr = nullptr)
        {
            if (instance != nullptr)
            {
                delete instance;
            }
            instance = rawPtr;
        }

    private:
        // Puntero estático al objeto gestionado.
        static T* instance; 
    };

}