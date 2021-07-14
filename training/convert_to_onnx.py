"""
This code is used to convert the pytorch models into an onnx format models.
"""
import torch.onnx
from net.VGG_192x192 import VGG_192x192
model_path = "./VGG_192x192_models/20.pth"
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
checkpoint = torch.load(model_path, map_location=device)
net = VGG_192x192()
net.load_state_dict(checkpoint)
net.eval()
net.to(device)
model_path = f"./VGG_192x192_models/20.onnx"
dummy_input = torch.randn(1, 3, 192, 192).to(device)
torch.onnx.export(net, dummy_input, model_path, export_params=True, verbose=False, input_names=['input'], output_names=['out'], opset_version=11)
