#include "model/icon.h"

Icon::Icon()
{
    // Default constructor needed for creating a QVector of type Icon
    // TODO: Find out if there is a more elegant solution
}

Icon::Icon(QImage image)
{
    link = nullptr;
    this->image = image;
}

Icon::Icon(Icon* linkTo)
{
    link = linkTo;
}

bool Icon::addClassification(
        std::shared_ptr<IconClassification> newClassification)
{
    // Check all existing classifications for possible conflicts
    for (std::shared_ptr<IconClassification> classification : classifications) {
        if(newClassification->isConflicting(classification.get())) {
            return false;
        }
    }

    this->classifications.append(newClassification);
    return true;
}

bool Icon::insertIntoClassification(
            std::shared_ptr<IconClassification> newClassification)
{
    bool success = addClassification(newClassification);
    if (success) {
        // Perform InsertCommands on Icon's image data upon insertion
        newClassification->performInsertCommandChain(image);
    }

    return success;
}

bool Icon::isOfLinkType() const
{
    // If link is set, then the Icon is of "link" type
    if (link) {
        return true;
    } else {
        return false;
    }
}

QImage const &Icon::getRepresentativeImage() const
{
    // If icon is link, return original icon's image data
    if (isOfLinkType()) {
        return link->getRepresentativeImage();
    } else {
        return image;
    }
}
