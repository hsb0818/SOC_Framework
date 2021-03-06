#pragma once

//#include <stdarg.h>
#include <vector>
#include <string>

#include "Rendering.h"
#include "Frustum.h"
#include "Sphere.h"

namespace Rendering
{
	class Object
	{
	protected:
		int renderQueue;
		std::vector<Object*> childs;
		bool use;
		bool isLight;
		bool culled;

	protected:
		SOC_Vector3 forward;
		SOC_Vector3 right;
		SOC_Vector3 up;

		SOC_Vector3 position;
		SOC_Vector3 localPosition;

		SOC_Quaternion rotation;

		SOC_Vector3 scale;
		SOC_Vector3 localScale;

		SOC_Vector3 eulerAngles;
		SOC_Vector3 localEulerAngles;

		SOC_MatrixA16 matrix;

		float radius;

	protected:
		Object *parent;
		Object *root;

	public:
		std::string name;
		std::string tag;
		std::string layer;

	public:
		Object(Object* parent = NULL);
		virtual ~Object(void);

	public:
		virtual bool Update();
		void Render(std::vector<Object*> *lights);

		virtual bool Intersect(Intersection::Sphere &sphere);

	protected:
		virtual void _Render(std::vector<Object*> *lights);

	private:
		enum FIND_ENUM{FIND_ENUM_NAME, FIND_ENUM_TAG};
		std::vector<Object*> _FindChild(std::string str, FIND_ENUM e, bool one);

	public:
		std::vector<Object*> FindChilds(std::string name);
		std::vector<Object*> FindChildsWithTag(std::string tag);

		Object* FindChild(std::string name);
		Object* FindChildWithTag(std::string tag);

		void AddChild(Object *child, bool copy = false);
		void AddChild(Object *child, int renderQueueOrder, bool copy = false);

		void DeleteChild(Object *child, bool remove);
		void DeleteAllChilds(bool remove);

	public:
		void LookAt(Object *target);
		void LookAt(SOC_Vector3 worldPosition);
		void LookAt(Object *target, SOC_Vector3 worldUp);
		void LookAt(SOC_Vector3 worldPosition, SOC_Vector3 worldUp);

		void Rotate(SOC_Vector3 eulerAngles);
		void Rotate(SOC_Vector3 axis, float angle);
		void Rotate(float x, float y, float z);

		void Translate(SOC_Vector3 translation);
		void TranslateWithUpVec(float units);
		void TranslateWithForwardVec(float units);
		void TranslateWithRightVec(float units);

		void Billboard(Object *camera, SOC_Matrix *outMatrix);

		bool IsChildOf(Object *parent);
		bool Culling(Frustum *frustum);

	protected:
		void UpdateMatrix();
	public:
		void UpdateWorldTransform();

	public:
		void SetPosition(SOC_Vector3 position);		
		void SetRotation(SOC_Quaternion quaternion);				
		void SetScale(SOC_Vector3 scale);
		void SetEulerAngles(SOC_Vector3 euler);
		void SetDirection(SOC_Vector3 dir);

	private:
		void Roll(float angle);
		void Yaw(float angle);
		void Pitch(float angle);

	public:
		void GetMatrix(SOC_Matrix *outMatrix);
		void GetWorldMatrix(SOC_Matrix *outMatrix);

		int GetChildCount();
		Object* Getchild(int index);
		float GetRadius();
		SOC_Vector3 GetWorldPosition();
		SOC_Vector3 GetLocalPosition();

		void SetUse(bool is);
		bool GetUse();
		bool IsLight();
		bool Culled();

	public:
		void UpdateChild();

	public:
		static Object* Copy(Object *obj);
	};

}