#include <ConsoleUI/ConsoleUI.hpp>
#include <sstream>
#include <conio.h>

#include <utils/MenuBuilder.hpp>

void testBuilder()
{
	using namespace ui;

	ConsoleUI ui;

	MenuBuilder builder;
	auto menu = builder.addItem("Item1")
			.addItem("Item2")
			.addSubmenu("Sub1").addItem("Item3")
								.addSubmenu("Sub2").addItem("Item4")
								.endSubmenu()
								.addItem("Item5")
			.endSubmenu()
			.addItem("Item6")
			.endSubmenu()
		.build();

	auto container = createSimpleContainer("Simple title", std::move(menu));
	auto listener = createEventListener();
	
	ui.setContainer(std::move(container));
	ui.setEventListener(std::move(listener));

	ui.start();
}

int main()
{
	//testBuilder();

	using namespace ui;

	auto title = createTitle("Sample title");

	auto helper = createHelper();
	helper->addHelper("i", "increment");
	helper->addHelper("j", "log");

	int counter = 1;
	bool isDirty = false;
	ConsoleUI ui;

	auto eventListener = createEventListener();
	eventListener->registerEventHandler(EVENT_TYPE::START, [&ui]() {ui.log("hello from start"); });
	eventListener->registerEventHandler(EVENT_TYPE::EXIT, [&ui]() {ui.log("exited"); });
	eventListener->registerEventHandler(EVENT_TYPE::UP, [&ui]() {ui.log("up pressed"); });
	eventListener->registerEventHandler(EVENT_TYPE::DOWN, [&ui]() {ui.log("down pressed"); });
				 
	eventListener->registerKeyPressEventHandler('j', [&ui]() {ui.log("j key pressed"); });
	eventListener->registerKeyPressEventHandler('i', [&counter, &isDirty]() {counter++; isDirty = true; });

	auto menu = createMenu();
	menu->createItem("Item 1", [&ui]() {ui.log("Item 1 was pressed"); });
	auto sub1 = menu->createSubmenu("Sub 1", [&ui]() {ui.log("Entered submenu 1"); });
	menu->createItem("Item 2", [&ui]() {ui.log("Item 2 was pressed"); });
	menu->createItem("Item 3", [&ui]() {ui.log("Item 3 was pressed"); });

	sub1.createItem("Item 1 in Sub 1", [&ui]() {ui.log("Item 1 in submenu 1"); });
	sub1.createItem("Item 2 in Sub 1", [&ui]() {ui.log("Item 2 in submenu 1"); });
	auto sub1it3 = sub1.createSubmenu("Sub2", [&ui]() {ui.log("Inside sub2"); }, [&ui]() {ui.log("Out of sub2"); });
	sub1it3.createItem("Item1 in sub2", [&ui]() {ui.log("item1 in sub2"); });
	sub1it3.createItem("Item2 in sub2", [&ui]() {ui.log("item2 in sub2"); });
	
	auto dyn1 = menu->createItem("Dynamic Item", NO_OP_CB, [&counter]() {return std::to_string(counter);});

	auto container = createContainer(
		std::move(title),
		std::move(menu),
		std::make_unique<ConsoleLog>(),
		std::move(helper)
	);

	ui.setContainer(std::move(container));
	ui.setEventListener(std::move(eventListener));

	ui.setUpdateCallback([&]() 
	{
		if (isDirty)
		{
			dyn1.update();
			isDirty = false;
		}
	});

	isDirty = true;

	ui.start();

	return 0;
}