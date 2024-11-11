#pragma once

namespace EngineUtilities {
	/**
	 * Clase TSharedPointer para manejar la gestión de memoria compartida.
	 *
	 * La clase TSharedPointer gestiona la memoria de un objeto de tipo T y lleva un
	 * recuento de referencias para permitir la compartición segura de un mismo objeto
	 * en múltiples instancias de TSharedPointer.
	 */
	template<typename T>
	class TSharedPointer
	{
	public:
		// Constructor por defecto.
		TSharedPointer() : ptr(nullptr), refCount(nullptr) {}

		// Constructor que toma un puntero crudo.
		explicit TSharedPointer(T* rawPtr) : ptr(rawPtr), refCount(new int(1)) {}

		// Constructor desde un puntero crudo y un recuento de referencias.
		TSharedPointer(T* rawPtr, int* existingRefCount) : ptr(rawPtr), refCount(existingRefCount)
		{
			if (refCount)
			{
				++(*refCount);
			}
		}

		// Constructor de copia.
		TSharedPointer(const TSharedPointer<T>& other) : ptr(other.ptr), refCount(other.refCount)
		{
			if (refCount)
			{
				++(*refCount);
			}
		}

		// Constructor de movimiento.
		TSharedPointer(TSharedPointer<T>&& other) noexcept : ptr(other.ptr), refCount(other.refCount)
		{
			other.ptr = nullptr;
			other.refCount = nullptr;
		}


		// Operador de asignación de copia.
		TSharedPointer<T>& operator=(const TSharedPointer<T>& other)
		{
			if (this != &other)
			{
				// Disminuir el recuento de referencias del objeto actual
				if (refCount && --(*refCount) == 0)
				{
					delete ptr;
					delete refCount;
				}
				// Copiar datos del otro puntero compartido
				ptr = other.ptr;
				refCount = other.refCount;
				if (refCount)
				{
					++(*refCount);
				}
			}
			return *this;
		}


		// Operador de asignación de movimiento.
		TSharedPointer<T>& operator=(TSharedPointer<T>&& other) noexcept
		{
			if (this != &other)
			{
				// Liberar el objeto actual
				if (refCount && --(*refCount) == 0)
				{
					delete ptr;
					delete refCount;
				}
				// Transferir los datos del otro puntero compartido
				ptr = other.ptr;
				refCount = other.refCount;
				other.ptr = nullptr;
				other.refCount = nullptr;
			}
			return *this;
		}

		// Destructor.
		~TSharedPointer()
		{
			if (refCount && --(*refCount) == 0)
			{
				delete ptr;
				delete refCount;
			}
		}

		// Operador de desreferenciación.
		T& operator*() const { return *ptr; }

		// Operador de acceso a miembros.
		T* operator->() const { return ptr; }

		// Agregar una función para comprobar si el puntero es válido
		operator bool() const {
			return ptr != nullptr;
		}


		// Obtener el puntero crudo.
		T* get() const { return ptr; }

		// Comprobar si el puntero es nulo.
		bool isNull() const { return ptr == nullptr; }


	public:
		// Puntero al objeto gestionado.
		T* ptr;
		// Puntero al recuento de referencias.
		int* refCount; 


		// Método swap.
		void swap(TSharedPointer<T>& other) noexcept
		{
			T* tempPtr = other.ptr;
			int* tempRefCount = other.refCount;

			other.ptr = this->ptr;
			other.refCount = this->refCount;

			this->ptr = tempPtr;
			this->refCount = tempRefCount;
		}

		// Libera el objeto actual y opcionalmente asigna un nuevo objeto.
		void reset(T* newPtr = nullptr)
		{
			// Disminuir el recuento de referencias del objeto actual
			if (refCount && --(*refCount) == 0)
			{
				delete ptr;
				delete refCount;
			}

			// Si newPtr es nullptr, asignar nullptr al puntero y recuento de referencias
			if (newPtr == nullptr)
			{
				ptr = nullptr;
				refCount = nullptr;
			}
			else
			{
				// Asignar nuevo objeto y manejar el recuento de referencias
				ptr = newPtr;
				refCount = new int(1);
			}
		}

		// Método de conversión para hacer cast dinámico
		template<typename U>
		TSharedPointer<U> dynamic_pointer_cast() const {
			// Intenta convertir el puntero de tipo T a U
			U* castedPtr = dynamic_cast<U*>(ptr);
			if (castedPtr) {
				// Si la conversión es exitosa, devuelve un nuevo TSharedPointer<U>
				return TSharedPointer<U>(castedPtr, refCount);
			}
			else {
				// Si falla la conversión, devuelve un TSharedPointer<U> nulo
				return TSharedPointer<U>();
			}
		}
	};


	// Función de utilidad para crear un TSharedPointer.
	template<typename T, typename... Args>
	TSharedPointer<T> MakeShared(Args... args)
	{
		return TSharedPointer<T>(new T(args...));
	}
}