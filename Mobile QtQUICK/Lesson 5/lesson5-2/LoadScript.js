function createSpriteObjects(parent, objName) {
    var component = Qt.createComponent(objName + ".qml");
    var sprite = component.createObject(parent, {x: 0, y: 0});
    if (sprite === null) {
        console.log("Error creating object"); // Error Handling
    }
}
