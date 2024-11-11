#pragma once

namespace EngineUtilities {
    /**
   * Clase TUniquePtr para manejo exclusivo de memoria.
   *
   * La clase TUniquePtr gestiona la memoria de un objeto de tipo T y garantiza
   * que solo una instancia de TUniquePtr puede poseer y gestionar el objeto en
   * cualquier momento.
   */
    template<typename T>
    class TUniquePtr
    {
    public:
        // Constructor por defecto.
        TUniquePtr() : ptr(nullptr) {}

        // Constructor que toma un puntero crudo.
        explicit TUniquePtr(T* rawPtr) : ptr(rawPtr) {}

        // Constructor de movimiento.
        TUniquePtr(TUniquePtr<T>&& other) noexcept : ptr(other.ptr) {
            other.ptr = nullptr;
        }

        // Operador de asignación de movimiento.
        TUniquePtr<T>& operator=(TUniquePtr<T>&& other) noexcept {
            if (this != &other) {
                // Liberar el objeto actual
                delete ptr;

                // Transferir los datos del otro puntero exclusivo
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        // Destructor.
        ~TUniquePtr() {
            delete ptr;
        }

        // Prohibir la copia de TUniquePtr
        TUniquePtr(const TUniquePtr<T>&) = delete;
        TUniquePtr<T>& operator=(const TUniquePtr<T>&) = delete;

        // Operador de desreferenciación.
        T& operator*() const { return *ptr; }

        // Operador de acceso a miembros.
        T* operator->() const { return ptr; }

        // Obtener el puntero crudo.
        T* get() const { return ptr; }

        // Liberar la propiedad del puntero crudo.
        T* release() {
            T* oldPtr = ptr;
            ptr = nullptr;
            return oldPtr;
        }

        // Reiniciar el puntero gestionado.
        void reset(T* rawPtr = nullptr) {
            delete ptr;
            ptr = rawPtr;
        }

        // Verificar si el puntero es nulo.
        bool isNull() const {
            return ptr == nullptr;
        }
    private:
        // Puntero al objeto gestionado.
        T* ptr; 
    };

    // Función de utilidad para crear un TUniquePtr.
    template<typename T, typename... Args>
    TUniquePtr<T> MakeUnique(Args... args) {
        return TUniquePtr<T>(new T(args...));
    }
}