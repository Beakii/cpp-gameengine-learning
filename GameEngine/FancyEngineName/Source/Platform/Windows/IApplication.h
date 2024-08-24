#pragma once

#define ENTRYAPP(x) IApplication* CreateApplication() { return new x(); }

class FANCY_ENGINE_API IApplication {
public:
	IApplication();
	virtual ~IApplication() {};

public:
	virtual void Initialize() =0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;
};

IApplication* CreateApplication();