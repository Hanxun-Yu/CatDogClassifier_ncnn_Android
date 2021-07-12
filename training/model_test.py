import argparse
import time
import numpy as np
import torch
from torchvision import transforms
import cv2
from net.VGG_192x192 import VGG_192x192
model_path = "./model/20.pth"
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
checkpoint = torch.load(model_path, map_location=device)
VGG = VGG_192x192().to(device)
VGG.load_state_dict(checkpoint)
VGG.eval()
# plfd_backbone = plfd_backbone.to(device)
transform = transforms.Compose([transforms.ToTensor(),
                               transforms.Normalize([0.5, 0.5, 0.5],[0.5, 0.5, 0.5])])

def main(raw_img):
    input = cv2.resize(raw_img, (48, 48))
    input = transform(input).unsqueeze(0).to(device)  # range [0, 255] -> [0.0,1.0]
    out = VGG(input)
    print(out)
    _, predicted = torch.max(out.data, 1)
    return predicted


if __name__ == '__main__':
    img = cv2.imread("./white_wall_1863.jpg")
    probability = main(img)
    if probability == 0:
        print("cover")
    else:
        print("nocover")