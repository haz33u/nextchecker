#include "InventoryItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UInventoryItemWidget::Setup(const FInventoryItemStruct& ItemData)
{
    if (ItemNameText)
    {
        ItemNameText->SetText(FText::FromString(ItemData.ItemName));
    }
    if (ItemIconImage)
    {
        ItemIconImage->SetBrushFromTexture(ItemData.ItemIcon);
    }
}
