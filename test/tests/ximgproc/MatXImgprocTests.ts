import { generateAPITests } from '../../utils/generateAPITests';
import { assertMetaData } from '../../utils/matTestUtils';
import { TestContext } from '../model';

export default (ctxt: TestContext) => {
  const { cv } = ctxt;

  describe('guidedFilter', () => {
    if (!cv.modules.ximgproc) {
      it('compiled without ximgproc');
      return;
    }

    const getDut = () => new cv.Mat(100, 100, cv.CV_8UC3);

    const guide = new cv.Mat(100, 100, cv.CV_8UC3);
    const radius = 3;
    const eps = 100;
    const ddepth = -1;
    generateAPITests({
      getDut,
      methodName: 'guidedFilter',
      methodNameSpace: 'Mat',
      getRequiredArgs: () => ([
        guide,
        radius,
        eps,
      ]),
      getOptionalArg: () => ddepth,
      expectOutput: (res) => {
        assertMetaData(res)(100, 100, cv.CV_8UC3);
      },
    });
  });
};