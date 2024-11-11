#pragma once
#include "TSharedPointer.h"

namespace EngineUtilities {
	/**
	* Clase TWeakPointer para observar objetos gestionados por TSharedPointer sin aumentar el recuento de referencias.
	*
	* La clase TWeakPointer proporciona una manera de observar un objeto gestionado por un TSharedPointer
	* sin tener influencia sobre el recuento de referencias del objeto. Permite acceder al objeto solo si
	* aún existe.
	*/
	template<typename T>
	class TWeakPointer
	{
	public:

		// Constructor por defecto.
		TWeakPointer() : ptr(nullptr), refCount(nullptr) {}

		// Constructor que toma un TSharedPointer.
		TWeakPointer(const TSharedPointer<T>& sharedPtr)
			: ptr(sharedPtr.ptr), refCount(sharedPtr.refCount) {}

		// Convertir TWeakPointer a TSharedPointer.
		TSharedPointer<T> lock() const
		{
			if (refCount && *refCount > 0)
			{
			return TSharedPointer<T>(ptr, refCount);
			}
			return TSharedPointer<T>();
		}

		// Hacer que TSharedPointer sea un amigo para acceder a los miembros privados.
		template<typename U>
		friend class TSharedPointer;

	private:
		// Puntero al objeto observado.
		T* ptr;
		// Puntero al recuento de referencias del TSharedPointer original.
		int* refCount; 
	};
}