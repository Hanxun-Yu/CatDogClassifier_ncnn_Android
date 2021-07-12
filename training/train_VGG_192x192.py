import torch
import torch.nn as nn
import torchvision
from torch.utils.data import DataLoader
from torch.autograd import Variable
import matplotlib.pyplot as plt
import torchvision.transforms as transforms
from net.VGG_192x192 import VGG_192x192
import os


def save_checkpoint(state, filename='checkpoint.pth.tar'):
    torch.save(state, filename)
    print('Save checkpoint to {0:}'.format(filename))


img_size = 192
BARCH_SIZE = 32
LR = 0.0001
EPOCH = 200
save_model_path = "./VGG_192x192_models/"

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(torch.cuda.is_available())
normalize = transforms.Normalize(mean=[0.5, 0.5, 0.5], std=[0.5, 0.5, 0.5])
transform = transforms.Compose([
    transforms.Resize(size=(img_size, img_size)),
    transforms.RandomRotation(20),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(),  # 将图片转换为Tensor,归一化至[0,1]
    normalize
])
train_dataset = torchvision.datasets.ImageFolder(root=r'\\10.1.1.125\Development\ShareFolder\dog_cat_data\train', transform=transform)
train_loader = torch.utils.data.DataLoader(train_dataset, batch_size=BARCH_SIZE, shuffle=True)

validation_dataset = torchvision.datasets.ImageFolder(root=r'\\10.1.1.125\Development\ShareFolder\dog_cat_data\test', transform=transform)
test_loader = torch.utils.data.DataLoader(validation_dataset, batch_size=32, shuffle=True)

VGGNet = VGG_192x192(2).to(device)
pthfile = r'./VGG_192x192_models/180.pth'
VGGNet.load_state_dict(torch.load(pthfile))

#alexNet = alexNet(pretrained=True)
#alexNet = torch.load("./alexNet.pth")
criterion = nn.CrossEntropyLoss()
opti = torch.optim.Adam(VGGNet.parameters(), lr=LR)

if __name__ == '__main__':
    Accuracy_list = []
    Loss_list = []

    for epoch in range(EPOCH):
        sum_loss = 0.0
        correct1 = 0

        total1 = 0
        for i, (images, labels) in enumerate(train_loader):
            num_images = images.size(0)
            images = Variable(images.to(device))
            labels = Variable(labels.to(device))
            out = VGGNet(images).to(device)
            _, predicted = torch.max(out.data, 1)
            total1 += labels.size(0)
            correct1 += (predicted == labels).sum().item()
            loss = criterion(out, labels)
            opti.zero_grad()
            loss.backward()
            opti.step()
            sum_loss += loss.item()
            if i % 50 == 0:
                print("EPOCH:", epoch, " Iteration :", i," Ave loss:", sum_loss / 50, " lr:",LR)
                sum_loss = 0.0
        Accuracy_list.append(100.0 * correct1 / total1)
        print('train accurary={}'.format(100.0 * correct1 / total1))
        Loss_list.append(loss.item())
        correct = 0
        test_loss = 0.0
        test_total = 0
        test_total = 0
        VGGNet.eval()
        for data in test_loader:
            images, labels = data
            images = Variable(images.to(device))
            labels = Variable(labels.to(device))
            outputs = VGGNet(images)
            _, predicted = torch.max(outputs.data, 1)
            loss = criterion(outputs, labels)
            test_loss += loss.item()
            test_total += labels.size(0)
            correct += (predicted == labels).sum().item()

        print('test  %d epoch loss: %.3f  acc: %.3f ' % (epoch + 1, test_loss / test_total, 100 * correct / test_total))
        if epoch % 20 == 0:
            filename = os.path.join(save_model_path, str(epoch) + '.pth')
            save_checkpoint(VGGNet.state_dict(), filename)

    x1 = range(0, EPOCH)
    x2 = range(0, EPOCH)
    y1 = Accuracy_list
    y2 = Loss_list
    plt.subplot(2, 1, 1)
    plt.plot(x1, y1, 'o-')
    plt.title('Train accuracy vs. epoches')
    plt.ylabel('Train accuracy')
    plt.subplot(2, 1, 2)
    plt.plot(x2, y2, '.-')
    plt.xlabel('Train loss vs. epoches')
    plt.ylabel('Train loss')
    plt.savefig("accuracy_epoch" + (str)(EPOCH) + ".png")
    plt.show()