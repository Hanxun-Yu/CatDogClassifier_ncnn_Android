import torch
from torchvision import transforms
import cv2
from net.Resnet18_192x192 import ResNet18
model_path = "./ResNet18_192x192_models/80.pth"
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
checkpoint = torch.load(model_path, map_location=device)
ResNet18 = ResNet18().to(device)
ResNet18.load_state_dict(checkpoint)
ResNet18.eval()
transform = transforms.Compose([transforms.ToTensor(),
                               transforms.Normalize([0.5, 0.5, 0.5],[0.5, 0.5, 0.5])])

def main(raw_img):
    input = cv2.resize(raw_img, (192, 192))
    input = transform(input).unsqueeze(0).to(device)
    out = ResNet18(input)
    print(out)
    _, predicted = torch.max(out.data, 1)
    return predicted


if __name__ == '__main__':
    img = cv2.imread("./test_pic/cat29.jpg")
    probability = main(img)
    if probability == 0:
        print("cat")
    else:
        print("dog")